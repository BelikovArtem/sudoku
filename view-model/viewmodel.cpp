#include "viewmodel.h"

ViewModel::ViewModel()
{
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &ViewModel::socketReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &ViewModel::socketDisconnected);

    socket->connectToHost("127.0.0.1", 5555);
}

ViewModel::~ViewModel()
{
    if (socket->state() == QTcpSocket::ConnectedState) {
        socket->disconnectFromHost();
    }
}

/*
 * PUBLIC SLOTS
 */
void ViewModel::handleLogIn(QString username, QString password) {
    if (socket->state() == QTcpSocket::ConnectedState) {
        /*
        * {
        *     "type": "select user",
        *     "user_name": "username",
        *     "user_password": "password"
        * }
        */
        QJsonObject request;
        request["type"] = "select user";
        request["user_name"] = username;
        request["user_password"] = password;

        sendRequestToServer(request);
    } else {
        emit errorServerDisconnected();
    }
}

void ViewModel::handleSignUp(QString username, QString password) {
    if (socket->state() == QTcpSocket::ConnectedState) {
        /*
        * {
        *     "type": "insert user",
        *     "user_name": "username",
        *     "user_password": "password"
        * }
        */
        QJsonObject request;
        request["type"] = "insert user";
        request["user_name"] = username;
        request["user_password"] = password;

        sendRequestToServer(request);
    } else {
        emit errorServerDisconnected();
    }
}

void ViewModel::handleCellClicked(QPushButton *cell, int row, int col)
{
    cellInFocus = cell;
    Cell::Position pos { row, col };
    game.setFocus(pos);
}

void ViewModel::handleNumberEntered(int number)
{
    game.openCell(number);

    game.checkWin();

    emit redrawCell(cellInFocus, number);
}

void ViewModel::handleNewGame(int difficultyLevel)
{
    QString level = "low";

    if (socket->state() == QTcpSocket::ConnectedState) {
        switch (difficultyLevel) {
        case 1:
            level = "medium";
            break;
        case 2:
            level = "high";
            break;
        }

        // recieve random sudoku grid from server
        /*
        * {
        *     "type": "select grid",
        *     "difficultyLevel": "low" | "medium" | "high"
        * }
        */
        QJsonObject request;
        request["type"] = "select grid";
        request["difficultyLevel"] = level;

        sendRequestToServer(request);
    } else {
        QFile gridMarkup(":/example/map.txt");
        gridMarkup.open(QIODevice::ReadOnly);
        QString strGrid = QString(gridMarkup.readAll());
        gridMarkup.close();

        QList<Cell> grid;
        grid = gridFromString(strGrid);

        game.setGrid(grid);
        game.startGame();
    }
    emit newGameStarted(difficultyLevel);
}

void ViewModel::socketReadyRead()
{
    if (socket->waitForConnected(500)) {
        socket->waitForReadyRead(500);

        importData = socket->readAll();
        document = QJsonDocument::fromJson(importData, &documentError);

        if (documentError.error != QJsonParseError::NoError) {
            emit warningJSONParseError();
            return;
        }

        auto obj = document.object();
        /*
        * {
        *     "status": "connected",
        *     "descriptor": socketDescriptor
        * }
        */
        if (obj["status"] == "connected" &&
            obj["descriptor"].toInt() > 0) {
            qDebug() << "Client connected successfully";
        }
        /*
        * {
        *     "source": "select user",
        *     "queryResult": "success" | "incorrect password" | "username not found",
        *     "user": user
        * }
        */
        else if (obj["source"] == "select user") {
            auto qRes = obj["queryResult"].toString();
            if (qRes == "success") {
                emit successfulLogIn();

                auto userObj = obj["user"].toObject();
                user.setId(userObj["user_id"].toInt());
                user.setUsername(userObj["user_name"].toString());
                user.setPassword(userObj["user_password"].toString());
            } else if (qRes == "incorrect password") {
                emit warningIncorrectPassword();
            } else if (qRes == "username not found") {
                emit warningUsernameNotFound();
            }
        }
        /*
        * {
        *     "source": "insert user",
        *     "queryResult": "success" | "username already exist",
        *     "user": user
        * }
        */
        else if (obj["source"] == "insert user") {
            auto qRes = obj["queryResult"].toString();
            if (qRes == "success") {
                emit successfulSignUp();

                auto userObj = obj["user"].toObject();
                user.setId(userObj["user_id"].toInt());
                user.setUsername(userObj["user_name"].toString());
                user.setPassword(userObj["user_password"].toString());
            } else {
                emit warningTakenUsername();
            }
        }
        /*
        * {
        *     "source": "select grid",
        *     "queryResult": grid
        * }
        */
        else if (obj["source"] == "select grid") {
            QList<Cell> grid = gridFromString(obj["queryResult"].toString());

            game.setGrid(grid);
            game.startGame();
        }
        else {
            emit warningUnknownJSON();
        }
    }
}

void ViewModel::socketDisconnected()
{
    socket->deleteLater();
}

/*
* PRIVATE METHODS
*/
void ViewModel::sendRequestToServer(const QJsonObject &request)
{
    exportData = QJsonDocument(request).toJson();
    socket->write(exportData);
    socket->waitForBytesWritten(500);
    exportData.clear();
}

QList<Cell> ViewModel::gridFromString(QString strGrid)
{
    QList<Cell> grid;
    char nextCharFromString;
    int number = 0, row = 0, col = 0;

    while (strGrid.length() >= 2) {
        // get first char of the string and convert it to the char
        nextCharFromString = strGrid.at(0).toLatin1();

        // skip whitespaces and new lines
        if (nextCharFromString == ' ' || nextCharFromString == '\n' ||
             nextCharFromString == '\r') {
            strGrid.removeAt(0);
            continue;
        }

        if (nextCharFromString >= '1' && nextCharFromString <= '9') {
            number = nextCharFromString - '0';   // convert char to int
            Cell::Position pos {
                row,            // i
                col             // j
            };

            // x - cell closed, else opened
            nextCharFromString = strGrid.at(1).toLatin1();

            Cell cell(number, nextCharFromString == 'x' ? false : true, pos);
            grid.append(cell);

            // remove 2 chars from the beggining of the string
            strGrid.remove(0, 2);

            col++;
        }

        if (col == 9) {
            row++;
            col = 0;
        }
    }
    return grid;
}
