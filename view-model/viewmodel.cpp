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
 * PUBLIC METHODS
 */


/*
 * PUBLIC SLOTS
 */
void ViewModel::handleLogIn(QString username, QString password) {
    if (socket->state() == QTcpSocket::ConnectedState) {
        /*
        * {
        *     "type": "select",
        *     "user_name": username,
        *     "user_password": password
        * }
        */
        exportData.append("{\n");
        exportData.append("\t\"type\": \"select\",\n");
        exportData.append("\t\"user_name\": \"" + username.toUtf8() + "\",\n");
        exportData.append("\t\"user_password\": \"" + password.toUtf8() + "\"\n");
        exportData.append("}\n");

        socket->write(exportData);
        socket->waitForBytesWritten(500);
        exportData.clear();
    } else {
        emit errorServerDisconnected();
    }
}

void ViewModel::handleSignUp(QString username, QString password) {
    if (socket->state() == QTcpSocket::ConnectedState) {
        /*
        * {
        *     "type": "insert",
        *     "user_name": username,
        *     "user_password": password
        * }
        */
        exportData.append("{\n");
        exportData.append("\t\"type\": \"insert\",\n");
        exportData.append("\t\"user_name\": \"" + username.toUtf8() + "\",\n");
        exportData.append("\t\"user_password\": \"" + password.toUtf8() + "\"\n");
        exportData.append("}\n");

        socket->write(exportData);
        socket->waitForBytesWritten(500);
        exportData.clear();
    } else {
        emit errorServerDisconnected();
    }
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
        if (obj.value("status").toString() == "connected" &&
            obj.value("descriptor").toInt() > 0) {
            qDebug() << "Client connected successfully";
        }
        /*
        * {
        *     "queryResult": "success" | "incorrect password" | "username not found",
        *     "source": "select"
        * }
        */
        else if (obj.value("source").toString() == "select" ){
            auto qRes = obj.value("queryResult").toString();
            if (qRes == "success") {
                emit successfulLogIn();
            } else if (qRes == "incorrect password") {
                emit warningIncorrectPassword();
            } else if (qRes == "username not found") {
                emit warningUsernameNotFound();
            }
        }
        /*
        * {
        *     "queryResult": "success" | "username already exist",
        *     "source": "insert"
        * }
        */
        else if (obj.value("source").toString() == "insert") {
            auto qRes = obj.value("queryResult").toString();
            if (qRes == "success") {
                emit successfulSignUp();
            } else {
                emit warningTakenUsername();
            }
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
