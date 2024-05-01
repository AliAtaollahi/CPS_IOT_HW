#ifndef LOGINHISTORY_H
#define LOGINHISTORY_H

#include <QObject>
#include <QDateTime>
#include <QString>


class LoginHistory
{
public:
    LoginHistory();
    LoginHistory(QString username, QString date, QString time, bool permited = false);

    QString getUsername() const;
    QString getDate() const;
    QString getTime() const;
    bool isPermitted() const;

private:
    QString username_;
    QString date_;
    QString time_;
    bool permited_;
};

#endif // LOGINHISTORY_H
