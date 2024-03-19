#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // draw background
    QPixmap bkgnd(":/icons/images/background.png");
    bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * PUBLIC SLOTS
 */
void MainWindow::slotLogIn(QString username, QString password)
{

}

void MainWindow::slotSignUp(QString username, QString password)
{

}

/*
 * PRIVATE SLOTS
 */
void MainWindow::on_pushButtonNewGame_clicked()
{

}

void MainWindow::on_pushButtonAuthorization_clicked()
{
    LoginDialog *loginDialog = new LoginDialog(this);
    // connect login dialog`s signals to viewmodel`s slots
    connect(loginDialog, &LoginDialog::signalLogIn, &viewmodel, &ViewModel::handleLogIn);
    connect(loginDialog, &LoginDialog::signalSignUp, &viewmodel, &ViewModel::handleSignUp);
    // emited when logged in / signed up successfully
    connect(&viewmodel, &ViewModel::successfulLogIn, loginDialog, &LoginDialog::_success);
    connect(&viewmodel, &ViewModel::successfulSignUp, loginDialog, &LoginDialog::_success);
    loginDialog->show();
}
