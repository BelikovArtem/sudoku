#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    // draw background
    QPixmap bkgnd(":/icons/images/background.png");
    bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

/*
 * PUBLIC SLOTS
 */
void LoginDialog::_success()
{
    QMessageBox::information(this, "OK", "Successful authorization");
    accept();
}

void LoginDialog::_incorrectPassword()
{
    QMessageBox::warning(this, "Warning", "Incorrect password");
}

void LoginDialog::_usernameNotFound()
{
    QMessageBox::warning(this, "Warning", "Username not found");
}

void LoginDialog::_takenUsername()
{
    QMessageBox::warning(this, "Warning", "Username already taken");
}

/*
 * PRIVATE SLOTS
 */
void LoginDialog::on_pushButtonSignUp_clicked()
{
    username = ui->lineEditUsername->text();
    password = ui->lineEditPassword->text();

    if (!username.isEmpty() && !password.isEmpty()) {
        emit signalSignUp(username, password);
    } else {
        QMessageBox::warning(this, "Error. Founded empty string", "Please, enter username and password");
    }
}

void LoginDialog::on_pushButtonLogIn_clicked()
{
    username = ui->lineEditUsername->text();
    password = ui->lineEditPassword->text();

    if (!username.isEmpty() && !password.isEmpty()) {
        emit signalLogIn(username, password);
    } else {
        QMessageBox::warning(this, "Error. Founded empty string", "Please, enter username and password");
    }
}
