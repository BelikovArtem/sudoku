#include "serverviewmodel.h"

ServerViewModel::ServerViewModel(QObject *parent)
    : QObject{parent}
{
    // connect to user model signals
    connect(&m_user, &User::userIdChanged, this, &ServerViewModel::onUserIdChanged);
    connect(&m_user, &User::userNameChanged, this, &ServerViewModel::onUserNameChanged);
    connect(&m_user, &User::userPasswordChanged, this, &ServerViewModel::onUserPasswordChanged);

    // connect to server
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &ServerViewModel::socketReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &ServerViewModel::socketDisconnected);
    socket->connectToHost("127.0.0.1", 5555);

    // by default, client isn`t connected to the server
    m_isConnected = false;
    m_isAuthorized = false;
}

/*
 * SETTERS
 */
void ServerViewModel::setUserName(const QString &userName)
{
    if (m_isConnected) {
        /*
        * {
        *     "type": "update user_name",
        *     "oldUsername": "user_name"
        *     "newUsername": "user_name"
        * }
        */
        QJsonObject request;
        request["type"] = "update user_name";
        request["oldUsername"] = m_user.user_name();
        request["newUsername"] = userName;

        sendRequestToServer(request);

        m_user.setUserName(userName);
    } else {
        emit viewMessage("Server isn`t connected");
    }
}

void ServerViewModel::setUserPassword(const QString &userPassword)
{
    if (m_isConnected) {
        /*
        * {
        *     "type": "update user_password",
        *     "oldPassword": "user_password"
        *     "newPassword": "user_password"
        * }
        */
        QJsonObject request;
        request["type"] = "update user_password";
        request["oldPassword"] = m_user.user_password();
        request["newPassword"] = userPassword;

        sendRequestToServer(request);

        m_user.setUserPassword(userPassword);
    } else {
        emit viewMessage("Server isn`t connected");
    }
}

/*
 * AVAILIBLE FROM UI
 */
void ServerViewModel::getRandomGridFromServer(QString difficultyLevel)
{
    if (m_isConnected) {
        /*
        * {
        *     "type": "select grid",
        *     "difficultyLevel": "low" | "medium" | "high"
        * }
        */
        QJsonObject request;
        request["type"] = "select grid";
        request["difficultyLevel"] = difficultyLevel;

        sendRequestToServer(request);
    } else {
        QString grid = "4x 9x 7 5 8 6 2 3 1\r\n"
                       "8 3x 1x 9 2 7 5 4x 6x\r\n"
                       "5x 6 2x 3 1x 4x 9 8x 7x\r\n"
                       "9x 7 5 4 6 1 8 2 3\r\n"
                       "1x 8 6 2 3x 5 4 7 9\r\n"
                       "3 2 4 8 7 9x 6x 1 5x\r\n"
                       "7x 4x 3x 6 5 2 1 9 8\r\n"
                       "2x 5x 8x 1 9 3x 7 6x 4\r\n"
                       "6 1x 9 7 4x 8x 3x 5x 2x ";

        emit gridFromServer(grid);
    }
}

void ServerViewModel::logIn(QString username, QString password)
{
    if (m_isConnected) {
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
        emit viewMessage("Server isn`t connected");
    }
}

void ServerViewModel::signUp(QString username, QString password)
{
    if (m_isConnected) {
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
        emit viewMessage("Server isn`t connected");
    }
}

/*
 * PUBLIC SLOTS
 */
// FROM MODEL
void ServerViewModel::onUserIdChanged()
{
    emit userIdChanged();
}

void ServerViewModel::onUserNameChanged()
{
    emit userNameChanged();
}

void ServerViewModel::onUserPasswordChanged()
{
    emit userPasswordChanged();
}

// FROM SERVER
void ServerViewModel::socketReadyRead()
{
    if (socket->waitForConnected(500)) {
        socket->waitForReadyRead(500);

        importData = socket->readAll();
        document = QJsonDocument::fromJson(importData, &documentError);

        if (documentError.error != QJsonParseError::NoError) {
            emit viewMessage("JSON from server has error");
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
            m_isConnected = true;
            emit isConnectedChanged();
        }
        /*
        * {
        *     "source": "select user",
        *     "queryResult": "success" | "Incorrect password" | "Username not found",
        *     "user": user
        * }
        */
        else if (obj["source"] == "select user") {
            QString queryResult = obj["queryResult"].toString();

            if (queryResult == "success") {
                fillUserData(obj["user"].toObject());
            } else {
                emit viewMessage(queryResult);
            }
        }
        /*
        * {
        *     "source": "insert user",
        *     "queryResult": "success" | "Username already exist",
        *     "user": user
        * }
        */
        else if (obj["source"] == "insert user") {
            QString queryResult = obj["queryResult"].toString();

            if (queryResult == "success") {
                fillUserData(obj["user"].toObject());
            } else {
                emit viewMessage(queryResult);
            }
        }
        /*
        * {
        *     "source": "select grid",
        *     "queryResult": grid
        * }
        */
        else if (obj["source"] == "select grid") {
            QString queryResult = obj["queryResult"].toString();

            emit gridFromServer(queryResult);
        }
        /*
        * {
        *     "source": "update user_name",
        *     "queryResult": "Success" | "Username already exists"
        * }
        */
        else if (obj["source"] == "update user_name") {
            emit viewMessage(obj["queryResult"].toString());
        }
        /*
        * {
        *     "source": "update user_password",
        *     "queryResult": "Success" | "Old password entered"
        * }
        */
        else if (obj["source"] == "update user_password") {
            emit viewMessage(obj["queryResult"].toString());
        }
        else {
            emit viewMessage("Unknown JSON from server");
        }
    }
}

void ServerViewModel::socketDisconnected()
{
    m_isConnected = false;
    emit isConnectedChanged();
    socket->deleteLater();
}


/*
 * PRIVATE METHODS
 */
void ServerViewModel::fillUserData(const QJsonObject &userObject)
{
    m_user.setUserId(userObject["user_id"].toInt());
    m_user.setUserName(userObject["user_name"].toString());
    m_user.setUserPassword(userObject["user_password"].toString());

    // notify view about successful authorization
    m_isAuthorized = true;
    emit isAuthorizedChanged();
    emit viewMessage("Authorization completed");
}

void ServerViewModel::sendRequestToServer(const QJsonObject &request)
{
    exportData = QJsonDocument(request).toJson();
    socket->write(exportData);
    socket->waitForBytesWritten(500);
    exportData.clear();
}
