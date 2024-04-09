#ifndef SERVERVIEWMODEL_H
#define SERVERVIEWMODEL_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include "../models/user.h"

class ServerViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int userId READ userId NOTIFY userIdChanged)
    Q_PROPERTY(int userScore READ userScore NOTIFY userScoreChanged)
    Q_PROPERTY(bool isConnected READ isConnected NOTIFY isConnectedChanged)
    Q_PROPERTY(bool isAuthorized READ isAuthorized NOTIFY isAuthorizedChanged)
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(QString userPassword READ userPassword WRITE setUserPassword NOTIFY userPasswordChanged)

public:
    explicit ServerViewModel(QObject *parent = nullptr);

    /*
     * GETTERS
     */
    int userId() const { return m_user.user_id(); }
    bool isConnected() const { return m_isConnected; }
    bool isAuthorized() const { return m_isAuthorized; }
    int userScore() const { return m_user.user_score(); }
    QString userName() const { return m_user.user_name(); }
    QString userPassword() const { return m_user.user_password(); }

    /*
     * SETTERS
     */
    void setUserName(const QString &userName);
    void setUserPassword(const QString &userPassword);

    /*
     * AVAILIBLE FROM UI
     */
    Q_INVOKABLE void getLeaderboard(int userCount);
    Q_INVOKABLE void logIn(QString username, QString password);
    Q_INVOKABLE void signUp(QString username, QString password);
    Q_INVOKABLE void getRandomGridFromServer(QString difficultyLevel);

signals:
    void userIdChanged();
    void userNameChanged();
    void userScoreChanged();
    void isConnectedChanged();
    void isAuthorizedChanged();
    void userPasswordChanged();
    void viewMessage(const QString& message);
    void gridFromServer(const QString& grid);
    void leaderboardRecievedFromServer(const QVariantList &leaderboard);

public slots:
    /*
     * FROM MODEL
     */
    void onUserIdChanged();
    void onUserNameChanged();
    void onUserScoreChanged();
    void onUserPasswordChanged();

    /*
     * FROM SERVER
     */
    void socketReadyRead();
    void socketDisconnected();

private:
    User m_user;
    bool m_isConnected;
    bool m_isAuthorized;

    QTcpSocket *socket;
    QByteArray importData;
    QByteArray exportData;
    QJsonDocument document;
    QJsonParseError documentError;

    /*
     * PRIVATE METHODS
     */
    void fillUserData(const QJsonObject &userObject);
    void sendRequestToServer(const QJsonObject &request);
};

#endif // SERVERVIEWMODEL_H
