#ifndef SERVER_H
#define SERVER_H

#include <QFile>
#include <QSqlQuery>
#include <QTcpSocket>
#include <QTcpServer>
#include <QThreadPool>
#include <QJsonObject>
#include <QSqlDatabase>
#include <QJsonDocument>
#include <QJsonParseError>

class server : public QTcpServer
{
    Q_OBJECT
public:
    server(QObject *parent = nullptr);
    ~server();

public slots:
    void socketReadyRead();
    void socketDisconnected();

private:
    QTcpSocket *socket;
    QByteArray exportData;
    QByteArray importData;
    QSqlDatabase dataBase;
    QJsonDocument doc;
    QJsonParseError docError;

protected:
    void incomingConnection(qintptr socketDescriptor) override;
};

#endif // SERVER_H
