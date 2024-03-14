#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

/*
 * PUBLIC SLOTS
 */
void LoginDialog::slotSignUp()
{
    accept();
}

void LoginDialog::slotLogIn()
{
    accept();
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
