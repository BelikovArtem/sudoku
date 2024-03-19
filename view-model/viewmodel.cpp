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
        QMessageBox::warning(nullptr, "Error", "Server isn`t connected");
    }
}

void ViewModel::handleSignUp(QString username, QString password) {
    if (socket->state() == QTcpSocket::ConnectedState) {

    } else {
        QMessageBox::warning(nullptr, "Error", "Server isn`t connected");
    }
}

void ViewModel::socketReadyRead()
{
    if (socket->waitForConnected(500)) {
        socket->waitForReadyRead(500);

        importData = socket->readAll();
        document = QJsonDocument::fromJson(importData, &documentError);

        if (documentError.error != QJsonParseError::NoError) {
            QMessageBox::warning(nullptr, "Error", "Unknown JSON from server");
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
            qDebug() << "Client connected successfelly";
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
                QMessageBox::information(nullptr, "Success", "Logged In");
                emit successfulLogIn();
            } else if (qRes == "incorrect password") {
                QMessageBox::information(nullptr, "Warning", "Incorrect password");
            } else if (qRes == "username not found") {
                QMessageBox::information(nullptr, "Warning", "Username not found");
            }
        }


    }
}

void ViewModel::socketDisconnected()
{
    socket->deleteLater();
}
