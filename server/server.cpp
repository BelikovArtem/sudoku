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

server::~server()
{

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
         *     "type": "insert",
         *     "user_name": "username",
         *     "user_password": "password"
         * }
         */
        if (obj.value("type") == "insert") {
            QString user_name = doc.object().value("user_name").toString();
            QString user_password = doc.object().value("user_password").toString();

            QSqlQuery query(dataBase);

            QString strQuery = "INSERT INTO public.test_table(\n\t";
            strQuery += "user_name, user_password)\n\t";
            strQuery += "VALUES ('" + user_name + QString("', '") + user_password + QString("');");

            bool queryComplete = false;
            if (!query.exec(strQuery)) {
                qDebug() << "Username already exists";
            } else {
                queryComplete = true;
                qDebug() << "User created successfully";
            }

            /*
             * {
             *     "queryResult": "success" | "username already exist",
             *     "source": "insert"
             * }
             */
            exportData.append("{\n");
            exportData.append((QString("\t\"queryResult\": ") +
                               QString((queryComplete == true ? "\"success\"" : "\"username already exist\""))).toUtf8());
            exportData.append(",\n\t\"source\": \"insert\"\n");
            exportData.append("}");

            socket->write(exportData);
            socket->waitForBytesWritten(1000);
            exportData.append("\n");
        }
        /*
         * {
         *     "type": "select",
         *     "user_name": "username",
         *     "user_password": "password"
         * }
         */
        else if (obj.value("type") == "select" &&
                 !obj.value("user_password").toString().isEmpty()) {

            QString user_name = obj.value("user_name").toString();
            QString user_password = obj.value("user_password").toString();

            QSqlQuery query(dataBase);

            QString strQuery("SELECT user_password FROM public.users");
            strQuery.append(" WHERE public.users.user_name = '" + user_name + "'");

            if (query.exec(strQuery)) {
                QString user_password_from_database;

                while(query.next()) {
                    user_password_from_database = query.value(0).toString();
                }

                /*
                 * {
                 *     "queryResult": "success" | "incorrect password" | "username not found",
                 *     "source": "select"
                 * }
                 */
                exportData.append("{\n");
                if (user_password_from_database.isEmpty()) {
                    exportData.append("\t\"queryResult\": \"username not found\",\n");
                } else if (user_password_from_database == user_password) {
                    exportData.append("\t\"queryResult\": \"success\",\n");
                } else {
                    exportData.append("\t\"queryResult\": \"incorrect password\",\n");
                }
                exportData.append("\t\"source\": \"select\"\n");
                exportData.append("}\n");

                socket->write(exportData);
                socket->waitForBytesWritten(500);
            }

        } else {
            qDebug() << "Unknown Json document from client";

        }

        importData.append("\n");
        QFile import_log("C:/C++ projects/qt/sudoku/server/import_data.json");
        import_log.open(QIODevice::WriteOnly | QIODevice::Append);
        import_log.write(importData);
        import_log.close();
        importData.clear();

        QFile export_log("C:/C++ projects/qt/sudoku/server/export_data.json");
        export_log.open(QIODevice::WriteOnly | QIODevice::Append);
        export_log.write(exportData);
        export_log.close();
        exportData.clear();
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
    QString responce = "{\n";
    responce += "\t\"status\": \"connected\",\n";
    responce += "\t\"descriptor\": " + QString::number(socketDescriptor);
    responce += "\n}\n";

    exportData.append(responce.toUtf8());

    socket->write(exportData);
    socket->waitForBytesWritten(1000);

    QFile export_log("C:/C++ projects/qt/sudoku/server/export_data.json");
    export_log.open(QIODevice::WriteOnly | QIODevice::Append);
    export_log.write(exportData);
    export_log.close();
    exportData.clear();
}
