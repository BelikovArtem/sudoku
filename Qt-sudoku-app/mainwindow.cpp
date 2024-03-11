#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->centralWidget()->setStyleSheet(
        "background-image: url(\":/icons/images/background.png\"); background-position: center;"
    );

    // connect to server
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::socketReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::socketDisconnected);
    socket->connectToHost("127.0.0.1", 5555);
}

MainWindow::~MainWindow()
{
    disconnect(socket, &QTcpSocket::readyRead, this, &MainWindow::socketReadyRead);
    disconnect(socket, &QTcpSocket::disconnected, this, &MainWindow::socketDisconnected);
    socket->deleteLater();
    delete ui;
}

/*
 * PUBLIC SLOTS
 */
void MainWindow::socketReadyRead()
{
    if (socket->waitForConnected(500)) {
        socket->waitForReadyRead(500);
        importData = socket->readAll();

        doc = QJsonDocument::fromJson(importData, &docError);

        if (docError.error == QJsonParseError::NoError ) {
            /*
             * {
             *     "status": "server_status",
             *     "descriptor": socket_descriptor
             * }
             */
            if (doc.object().value("status") == "connected" &&
                doc.object().value("descriptor").toInt() > 0) {
                qDebug() << "Connection is established";

                // show authorization dialog
                LoginDialog *loginDialog = new LoginDialog(this);
                connect(loginDialog, &LoginDialog::signalLogIn, this, &MainWindow::slotLogIn);
                connect(loginDialog, &LoginDialog::signalSignUp, this, &MainWindow::slotSignUp);
                connect(this, &MainWindow::successfullSignUp, loginDialog, &LoginDialog::slotSignUp);
                connect(this, &MainWindow::successfullLogIn, loginDialog, &LoginDialog::slotLogIn);
                loginDialog->show();
            }
            /*
             * {
             *     "queryResult": "success" | "username not found" | "incorrect password",
             *     "source": "select"
             * }
             */
            else if (doc.object().value("source") == "select") {
                QString status = doc.object().value("queryResult").toString();
                if (status == "success") {
                    QMessageBox::information(this, "Success", "Logged In successfully");
                    emit successfullLogIn();
                } else if (status == "username not found") {
                    QMessageBox::information(this, "Error", "Username not found");
                } else {
                     QMessageBox::information(this, "Error", "Incorrect password");
                }
            }
            /*
             * {
             *     "queryResult": "success" | "username already exist",
             *     "source": "insert"
             * }
             */
            else if (doc.object().value("source") == "insert") {
                QString status = doc.object().value("queryResult").toString();
                if (status == "success") {
                    QMessageBox::information(this, "Success", "User created successfully");
                    emit successfullSignUp();
                } else {
                    QMessageBox::information(this, "Error", "Username aready exists");
                }
            }
            else {
                QMessageBox::warning(this, "Error", "Unknown Json from server");
            }
        } else {
            QMessageBox::warning(this, "Error", "Error with parsing json document from server");
        }
    }
}

void MainWindow::socketDisconnected()
{
    if (socket) {
        socket->disconnectFromHost();
        socket->deleteLater();
    }
}

/*
 * PRIVATE SLOTS
 */
void MainWindow::slotLogIn(QString username, QString password)
{
    this->username = username;
    this->password = password;

    if (socket->state() == QAbstractSocket::ConnectedState) {
        /*
         * {
         *     "type": "select",
         *     "user_name": "username",
         *     "user_password": "password"
         * }
         */
        exportData.append("{\n");
        exportData.append("\t\"type\": \"select\",\n");
        exportData.append("\t\"user_name\": \"" + username.toUtf8() + "\",\n");
        exportData.append("\t\"user_password\": \"" + password.toUtf8() + "\"\n");
        exportData.append("}");

        socket->write(exportData);
        socket->waitForBytesWritten(500);
        exportData.clear();
    } else {
        qDebug() << "Trying to select user, but socket isn`t connected to the server";
    }
}

void MainWindow::slotSignUp(QString username, QString password)
{
    this->username = username;
    this->password = password;

    if (socket->state() == QAbstractSocket::ConnectedState) {
        /*
         * {
         *     "type": "insert",
         *     "user_name": "username",
         *     "user_password": "password"
         * }
         */
        exportData.append("{\n");
        exportData.append("\t\"type\": \"insert\",\n");
        exportData.append("\t\"user_name\": \"" + username.toUtf8() + "\",\n");
        exportData.append("\t\"user_password\": \"" + password.toUtf8() + "\"\n");
        exportData.append("}");

        socket->write(exportData);
        socket->waitForBytesWritten(500);
        exportData.clear();
    } else {
        qDebug() << "Trying to insert user, but socket isn`t connected to the server";
    }
}

/*
 * CLOSE EVENT OVERRIDE
 */
