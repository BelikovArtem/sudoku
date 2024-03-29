#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QFile>
#include <QObject>
#include <QTcpSocket>
#include <QPushButton>
#include <QJsonObject>
#include <QJsonDocument>
#include <QStandardItem>
#include <QJsonParseError>
#include "../models/User.h"
#include "../models/Game.h"

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
    void handleCellClicked(int row, int col);
    void handleNewGame(int difficultyLevel);
    void handleNumberEntered(int number);

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
    Game game;
    Cell::Position cellInFocusPos;

    /*
     * PRIVATE METHODS
     */
    void sendRequestToServer(const QJsonObject &request);
    QList<Cell> gridFromString(QString strGrid);
    void requestDrawingGrid(QList<Cell> grid);

signals:
    void successfulSignUp();
    void successfulLogIn();
    void warningTakenUsername();
    void warningIncorrectPassword();
    void warningUsernameNotFound();
    void warningUnknownJSON();
    void warningJSONParseError();
    void errorServerDisconnected();
    void redrawCell(int index, int number);
};

#endif // VIEWMODEL_H
