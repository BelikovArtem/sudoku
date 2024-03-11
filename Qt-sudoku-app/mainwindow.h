#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QJsonArray>
#include <QTcpSocket>
#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QStandardItem>
#include <QJsonParseError>
#include "LoginDialog/logindialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots: 
    void socketReadyRead();
    void socketDisconnected();

signals:
    void successfullSignUp();
    void successfullLogIn();

private:
    Ui::MainWindow *ui;
    /*
     * PRIVATE FIELDS
     */
    QTcpSocket *socket = nullptr;
    QByteArray importData;
    QByteArray exportData;
    QString username;
    QString password;
    QJsonDocument doc;
    QJsonParseError docError;

private slots:
    void slotLogIn(QString username, QString password); // called from LoginDialog
    void slotSignUp(QString username, QString password); // called from LoginDialog

protected:
    // void closeEvent(QCloseEvent *event) override;
};
#endif // MAINWINDOW_H
