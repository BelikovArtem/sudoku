#ifndef SERVER_H
#define SERVER_H

#include <QFile>
#include <QSqlQuery>
#include <QTcpSocket>
#include <QTcpServer>
#include <QJsonArray>
#include <QJsonObject>
#include <QSqlDatabase>
#include <QJsonDocument>
#include <QJsonParseError>

class server : public QTcpServer
{
    Q_OBJECT
public:
    server(QObject *parent = nullptr);
    ~server() {};

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

    const QString exportLogPath = "C:/C++ projects/qt/sudoku/server/export_data.json";
    const QString importLogPath = "C:/C++ projects/qt/sudoku/server/import_data.json";

    /*
     * PRIVATE METHODS
     */
    void log(QByteArray &data, const QString& logFilePath);
    void sendResponceToClient(const QJsonObject &responce);

protected:
    void incomingConnection(qintptr socketDescriptor) override;
};

#endif // SERVER_H
