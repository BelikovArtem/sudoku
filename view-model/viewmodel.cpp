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

        exportData = QJsonDocument(request).toJson();
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
        *     "type": "insert user",
        *     "user_name": "username",
        *     "user_password": "password"
        * }
        */
        QJsonObject request;
        request["type"] = "insert user";
        request["user_name"] = username;
        request["user_password"] = password;

        exportData = QJsonDocument(request).toJson();
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
        if (obj["status"] == "connected" &&
            obj["descriptor"].toInt() > 0) {
            qDebug() << "Client connected successfully";
        }
        /*
        * {
        *     "source": "select user",
        *     "queryResult": "success" | "incorrect password" | "username not found",
        *     "user": user
        */
        else if (obj["source"] == "select user"){
            auto qRes = obj["queryResult"].toString();
            if (qRes == "success") {
                emit successfulLogIn();

                auto userObj = obj["user"].toObject();
                user.setId(userObj.value("user_id").toInt());
                user.setUsername(userObj.value("user_name").toString());
                user.setPassword(userObj.value("user_password").toString());
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
                user.setId(userObj.value("user_id").toInt());
                user.setUsername(userObj.value("user_name").toString());
                user.setPassword(userObj.value("user_password").toString());
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
