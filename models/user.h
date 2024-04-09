#ifndef USER_H
#define USER_H

#include <QObject>

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QObject *parent = nullptr);

    /*
     * GETTERS
     */
    int user_id() const { return m_user_id; }
    int user_score() const { return m_user_score; }
    QString user_name() const { return m_user_name; }
    QString user_password() const { return m_user_password; }

    /*
     * SETTERS
     */
    void setUserId(int id) { m_user_id = id; }
    void setUserScore(int score) { m_user_score = score; };
    void setUserName(const QString &userName) { m_user_name = userName; }
    void setUserPassword(const QString &userPassword) { m_user_password = userPassword; }

signals:
    void userIdChanged();
    void userNameChanged();
    void userScoreChanged();
    void userPasswordChanged();

private:
    int m_user_id;
    int m_user_score;
    QString m_user_name;
    QString m_user_password;
};

#endif // USER_H
