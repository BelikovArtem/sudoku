#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPushButton>
#include <QGridLayout>
#include <QMainWindow>
#include "../../view-model/viewmodel.h"
#include "../LoginDialog/logindialog.h"

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

private slots:
    void on_pushButtonNewGame_clicked();

    void on_pushButtonAuthorization_clicked();

private:
    Ui::MainWindow *ui;
    ViewModel viewmodel;
    /*
     * PRIVATE METHODS
     */

};
#endif // MAINWINDOW_H
