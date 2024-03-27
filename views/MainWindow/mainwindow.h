#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPushButton>
#include <QGridLayout>
#include <QMainWindow>
#include "../GameWindow/gamewindow.h"
#include "../LoginDialog/logindialog.h"
#include "../../view-model/viewmodel.h"
#include "../DifficultyLevelDialog/difficultyleveldialog.h"

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
    void handleUnknownJSON();
    void handleJSONParseError();
    void handleServerDisconnected();
    void showGameWindow(int difficultyLevel);

private slots:
    void on_pushButtonNewGame_clicked();

    void on_pushButtonAuthorization_clicked();

private:
    Ui::MainWindow *ui;
    ViewModel viewmodel;
};
#endif // MAINWINDOW_H
