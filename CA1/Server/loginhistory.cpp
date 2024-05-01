#include "loginhistory.h"

LoginHistory::LoginHistory() {}

LoginHistory::LoginHistory(QString username, QString date, QString time, bool permited)
    : username_(username), date_(date), time_(time), permited_(permited){}

QString LoginHistory::getUsername() const
{
    return username_;
}

QString LoginHistory::getTime() const
{
    return time_;
};

QString LoginHistory::getDate() const
{
    return date_;
};

bool LoginHistory::isPermitted() const
{
    return permited_;
};
