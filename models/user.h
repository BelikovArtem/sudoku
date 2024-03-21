#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User(QString name, QString password, int id) :
        user_name(name), user_password(password), user_id(id) {}

    User()
    {
        user_name = QString();
        user_password = QString();
        user_id = -1;
    }

    /*
     * GETTERS
     */
    QString getUsername() const { return user_name; }
    QString getPassword() const { return user_password; }
    int getId() const { return user_id; }

    /*
     * SETTERS
     */
    void setUsername(const QString &_user_name) { user_name = _user_name; }
    void setPassword(const QString &_user_password) { user_password = _user_password; }
    void setId(int _user_id) { user_id = _user_id; }

private:
    QString user_name;
    QString user_password;
    int user_id;
};

#endif // USER_H
