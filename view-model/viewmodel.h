#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QObject>
#include <QTcpSocket>
#include <QPushButton>
#include <QJsonObject>
#include <QJsonDocument>
#include <QStandardItem>
#include <QJsonParseError>
#include "../models/User.h"
//#include "../models/Game.h"

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
    /*
     * SERVER
     */
    QTcpSocket *socket;
    QByteArray importData;
    QByteArray exportData;
    QJsonDocument document;
    QJsonParseError documentError;
    /*
     * MODELS
     */
    User user;
    // Game game;

signals:
    void successfulSignUp();
    void successfulLogIn();
    void warningTakenUsername();
    void warningIncorrectPassword();
    void warningUsernameNotFound();
    void warningUnknownJSON();
    void warningJSONParseError();
    void errorServerDisconnected();
};

#endif // VIEWMODEL_H
