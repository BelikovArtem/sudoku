#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QObject>
#include <QTcpSocket>
#include <QMessageBox>
#include <QPushButton>
#include <QJsonObject>
#include <QJsonDocument>
#include <QStandardItem>
#include <QJsonParseError>

class ViewModel : public QObject
{

    Q_OBJECT

public:
    ViewModel();
    ~ViewModel();

public slots:
    void socketReadyRead();
    void socketDisconnected();
    void handleLogIn(QString username, QString password);
    void handleSignUp(QString username, QString password);

private:
    QTcpSocket *socket;
    QByteArray importData;
    QByteArray exportData;
    QJsonDocument document;
    QJsonParseError documentError;

signals:
    void successfulSignUp();
    void successfulLogIn();

};

#endif // VIEWMODEL_H
