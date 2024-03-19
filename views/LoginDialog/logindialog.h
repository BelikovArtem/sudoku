#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

public slots:
    void slotSignUp();
    void slotLogIn();

private slots:
    void on_pushButtonSignUp_clicked();

    void on_pushButtonLogIn_clicked();

private:
    /*
     * PRIVATE FIELDS
     */
    Ui::LoginDialog *ui;
    QString username;
    QString password;

signals:
    void signalLogIn(QString username, QString password);
    void signalSignUp(QString username, QString password);
};

#endif // LOGINDIALOG_H
