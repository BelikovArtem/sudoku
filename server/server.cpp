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
                    user["user_score"] = query.value(3).toInt();
                }
            }

            /*
             * {
             *     "source": "insert user",
             *     "queryResult": "success" | "Username already exist",
             *     "user": {
             *         "user_id": id
             *         "user_name": user_name",
             *         "user_password": "user_password",
             *     }
             * }
             */
            QJsonObject responce;
            responce["source"] = "insert user";
            responce["queryResult"] = queryComplete ? "success" : "Username already exists";
            responce["user"] = user;

            sendResponceToClient(responce);
        }
        /*
         * {
         *     "type": "select user",
         *     "user_name": "username",
         *     "user_password": "password"
         * }
         */
        else if (obj["type"] == "select user") {
            QString user_name = obj["user_name"].toString();
            QString user_password = obj["user_password"].toString();

            QSqlQuery query(dataBase);

            QString strQuery("SELECT * FROM public.users");
            strQuery.append(" WHERE public.users.user_name = '" + user_name + "'");

            if (query.exec(strQuery)) {
                QJsonObject user;

                while (query.next()) {
                    user["user_id"] = query.value(0).toInt();
                    user["user_name"] = query.value(1).toString();
                    user["user_password"] = query.value(2).toString();
                    user["user_score"] = query.value(3).toInt();
                }

                /*
                 * {
                 *     "source": "select user",
                 *     "queryResult": "success" | "Incorrect password" | "Username not found",
                 *     "user": {
                 *         "user_id": id,
                 *         "user_name": "name",
                 *         "user_password": "password"
                 *     }
                 * }
                 */
                QJsonObject responce;
                responce["source"] = "select user";
                if (user.isEmpty())
                    responce["queryResult"] = "Username not found";
                else if (user["user_password"] == user_password)
                    responce["queryResult"] = "success";
                else
                    responce["queryResult"] = "Incorrect password";
                responce["user"] = user;

                sendResponceToClient(responce);
            }
        }
        /*
        * {
        *     "type": "select grid",
        *     "difficultyLevel": "Low" | "Medium" | "High"
        * }
        */
        else if (obj["type"] == "select grid") {
            QString difficultyLevel = obj["difficultyLevel"].toString();

            QSqlQuery query(dataBase);

            QString strQuery("SELECT grid FROM public.grids ");
            strQuery.append("WHERE difficulty = '" + difficultyLevel.toLower() + "' ");
            strQuery.append(" ORDER BY RANDOM() ");
            strQuery.append("LIMIT 1");

            if (query.exec(strQuery)) {
                /*
                * {
                *     "source": "select grid",
                *     "queryResult": grid
                * }
                */
                QJsonObject responce;
                responce["source"] = "select grid";

                while (query.next()) {
                    responce["queryResult"] = query.value(0).toString();
                }

                sendResponceToClient(responce);
            }
        }
        /*
        * {
        *     "type": "update user_name",
        *     "oldUsername": "user_name"
        *     "newUsername": "user_name"
        * }
        */
        else if (obj["type"] == "update user_name") {
            QString oldUsername = obj["oldUsername"].toString();
            QString newUsername = obj["newUsername"].toString();

            QSqlQuery query(dataBase);

            QString strQuery("UPDATE public.users\n\t");
            strQuery.append("SET user_name = '" + newUsername + "'\n\t");
            strQuery.append("WHERE user_name = '" + oldUsername + "'\n");
            strQuery.append("RETURNING user_name");

            if (query.exec(strQuery)) {
                /*
                * {
                *     "source": "update user_name",
                *     "queryResult": "Success" | "Username already exists"
                * }
                */
                QJsonObject responce;
                responce["source"] = "update user_name";

                while (query.next()) {
                    responce["queryResult"] = query.value(0).toString() == newUsername ? "Success" :
                        "Username already exists";
                }

                sendResponceToClient(responce);
            }
        }
        /*
        * {
        *     "type": "update user_password",
        *     "oldPassword": "user_password"
        *     "newPassword": "user_password"
        * }
        */
        else if (obj["type"] == "update user_password") {
            QString oldPassword = obj["oldPassword"].toString();
            QString newPassword = obj["newPassword"].toString();

            QSqlQuery query(dataBase);

            QString strQuery("UPDATE public.users\n\t");
            strQuery.append("SET user_password = '" + newPassword + "'\n\t");
            strQuery.append("WHERE user_password = '" + oldPassword + "'\n");
            strQuery.append("RETURNING user_password");

            if (query.exec(strQuery)) {
                /*
                * {
                *     "source": "update user_password",
                *     "queryResult": "Success" | "Old password entered"
                * }
                */
                QJsonObject responce;
                responce["source"] = "update user_password";

                while (query.next()) {
                    responce["queryResult"] = query.value(0).toString() == newPassword ? "Success" :
                                                  "Old password entered";
                }

                sendResponceToClient(responce);
            }
        }
        /*
        * {
        *     "type": "select leaderboard",
        *     "userCount": userCount
        * }
        */
        else if (obj["type"] == "select leaderboard") {
            int userCount = obj["userCount"].toInt();

            QSqlQuery query(dataBase);

            QString strQuery = "SELECT user_name, user_score\n";
            strQuery.append("FROM public.users\n");
            strQuery.append("ORDER BY user_score DESC\n");
            strQuery.append("LIMIT " + QString::number(userCount));

            if (query.exec(strQuery)) {
                /*
                * {
                *     "source": "select leaderboard",
                *     "userCount" : userCount,
                *     "queryResult": users
                * }
                */
                QJsonObject responce;
                responce["source"] = "select leaderboard";

                int counter = 0;
                QJsonArray users;
                while (query.next()) {
                    QJsonObject user;
                    user["user_name"] = query.value(0).toString();
                    user["user_score"] = query.value(1).toInt();
                    users.append(user);
                    counter++;
                }
                responce["userCount"] = counter;
                responce["queryResult"] = users;

                sendResponceToClient(responce);
            }
        }
        /*
        * {
        *     "type": "update user_score",
        *     "user_name": "user_name",
        *     "newUserScore": score
        * }
        */
        else if (obj["type"] == "update user_score") {
            int score = obj["newUserScore"].toInt();
            QString user_name = obj["user_name"].toString();

            QSqlQuery query(dataBase);

            QString strQuery("UPDATE public.users\n\t");
            strQuery.append("SET user_score= " + QString::number(score) + "\n\t");
            strQuery.append("WHERE user_name = '" + user_name + "'\n");
            strQuery.append("RETURNING user_score");

            if (query.exec(strQuery)) {
                /*
                * {
                *     "source": "update user_score",
                *     "queryResult": newScore
                * }
                */
                QJsonObject responce;
                responce["source"] = "update user_score";

                while (query.next()) {
                    responce["queryResult"] = query.value(0).toInt();
                }

                sendResponceToClient(responce);
            }
        }
        else {
            qDebug() << "Unknown Json document from client";
        }

        log(importData, importLogPath);
        log(exportData, exportLogPath);

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

    sendResponceToClient(responce);
}

/*
* PRIVATE METHODS
*/
void server::log(QByteArray &data, const QString& logFilePath)
{
    QFile log(logFilePath);
    log.open(QIODevice::WriteOnly | QIODevice::Append);
    log.write(data);
    log.close();
    data.clear();
}

void server::sendResponceToClient(const QJsonObject &responce)
{
    exportData = QJsonDocument(responce).toJson();
    socket->write(exportData);
    socket->waitForBytesWritten(1000);
    log(exportData, exportLogPath);
    exportData.clear();
}
