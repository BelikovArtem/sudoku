#include "server.h"

server::server(QObject *parent) : QTcpServer(parent)
{
    // connect to database
    dataBase = QSqlDatabase::addDatabase("QPSQL");
    dataBase.setHostName("localhost");  // localhost is equal to 127.0.0.1
    dataBase.setDatabaseName("sudoku");
    dataBase.setUserName("postgres");

    QFile bddata("C:/C++ projects/qt/sudoku/server/bd_data.txt");
    bddata.open(QIODevice::ReadOnly);
    dataBase.setPassword(bddata.readAll());
    bddata.close();

    if (!dataBase.open()) {
        qDebug() << "Database is cannot be connected";
    } else {
        qDebug() << "Database is connected";
    }

    // start server
    if (this->listen(QHostAddress::Any, 5555)) {
        qDebug() << "Server is listening";
    } else {
        qDebug() << "Server isn`t listening";
    }
}

/*
 * PUBLIC SLOTS
 */
void server::socketReadyRead()
{
    importData = socket->readAll();

    doc = QJsonDocument::fromJson(importData, &docError);

    if (docError.error == QJsonParseError::NoError) {
        auto obj = doc.object();
        /*
         * {
         *     "type": "insert user",
         *     "user_name": "username",
         *     "user_password": "password"
         * }
         */
        if (obj["type"] == "insert user") {
            QString user_name = obj["user_name"].toString();
            QString user_password = obj["user_password"].toString();

            QSqlQuery query(dataBase);

            QString strQuery = "INSERT INTO public.users(\n\t";
            strQuery += "user_name, user_password)\n\t";
            strQuery += "VALUES ('" + user_name + QString("', '") + user_password + QString("') RETURNING *;");

            QJsonObject user;
            bool queryComplete = false;
            if (!query.exec(strQuery)) {
                qDebug() << "Username already exists";
            } else {
                queryComplete = true;
                qDebug() << "User created successfully";

                while (query.next()) {
                    user["user_id"] = query.value(0).toInt();
                    user["user_name"] = query.value(1).toString();
                    user["user_password"] = query.value(2).toString();
                }
            }

            /*
             * {
             *     "source": "insert user",
             *     "queryResult": "success" | "username already exist",
             *     "user":
             *     {
             *         "user_id": id
             *         "user_name": user_name",
             *         "user_password": "user_password",
             *     }
             * }
             */
            QJsonObject responce;
            responce["source"] = "insert user";
            responce["queryResult"] = queryComplete ? "success" : "username already exists";
            responce["user"] = user;

            exportData = QJsonDocument(responce).toJson();
            socket->write(exportData);
            socket->waitForBytesWritten(1000);
        }
        /*
         * {
         *     "type": "select user",
         *     "user_name": "username",
         *     "user_password": "password"
         * }
         */
        else if (obj["type"] == "select user") {
            QString user_name = obj.value("user_name").toString();
            QString user_password = obj.value("user_password").toString();

            QSqlQuery query(dataBase);

            QString strQuery("SELECT * FROM public.users");
            strQuery.append(" WHERE public.users.user_name = '" + user_name + "'");

            if (query.exec(strQuery)) {
                QJsonObject user;

                while(query.next()) {
                    user["user_id"] = query.value(0).toInt();
                    user["user_name"] = query.value(1).toString();
                    user["user_password"] = query.value(2).toString();
                }

                /*
                 * {
                 *     "source": "select user",
                 *     "queryResult": "success" | "incorrect password" | "username not found",
                 *     "user": {
                 *         "user_id": id,
                 *         "user_name": "name",
                 *         "user_password": "password"
                 * }
                 */
                QJsonObject responce;
                responce["source"] = "select user";
                if (user.isEmpty())
                    responce["queryResult"] = "username not found";
                else if (user["user_password"] == user_password)
                    responce["queryResult"] = "success";
                else
                    responce["queryResult"] = "incorrect password";
                responce["user"] = user;

                exportData = QJsonDocument(responce).toJson();
                socket->write(exportData);
                socket->waitForBytesWritten(500);
            }

        } else {
            qDebug() << "Unknown Json document from client";
        }

        logImport(importData);
        logExport(exportData);

    } else {
        qDebug() << "Parse error in Json from client " + docError.errorString();
    }
}

void server::socketDisconnected()
{
    qDebug() << "Client disconnected";
    socket->deleteLater();
}

/*
 * PROTECTED METHODS OVERRIDE
 */
void server::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, &QTcpSocket::readyRead, this, &server::socketReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &server::socketDisconnected);

    /*
     * {
     *     "status": "connected",
     *     "descriptor": socketDescriptor
     * }
     */
    QJsonObject responce;
    responce["status"] = "connected";
    responce["descriptor"] = socketDescriptor;

    exportData = QJsonDocument(responce).toJson();
    socket->write(exportData);
    socket->waitForBytesWritten(1000);
    logExport(exportData);
}

/*
* PRIVATE METHODS
*/
void server::logImport(QByteArray &data)
{
    data.append("\n");
    QFile import_log("C:/C++ projects/qt/sudoku/server/import_data.json");
    import_log.open(QIODevice::WriteOnly | QIODevice::Append);
    import_log.write(data);
    import_log.close();
    data.clear();
}

void server::logExport(QByteArray &data)
{
    data.append("\n");
    QFile export_log("C:/C++ projects/qt/sudoku/server/export_data.json");
    export_log.open(QIODevice::WriteOnly | QIODevice::Append);
    export_log.write(data);
    export_log.close();
    data.clear();
}
