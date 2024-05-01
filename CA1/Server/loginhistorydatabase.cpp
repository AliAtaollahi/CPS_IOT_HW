#include "loginhistorydatabase.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

LoginHistoryDatabase::LoginHistoryDatabase(const QString &initialDataPath, QObject *parent) : QObject(parent)
{
    readLoginHistoriesFromJson(initialDataPath);
}

const QVector<LoginHistory>& LoginHistoryDatabase::getLoginHistoriesVector() const
{
    return loginHistoryVector_;
}

void LoginHistoryDatabase::readLoginHistoriesFromJson(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open " + path;
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (!doc.isArray()) {
        qDebug() << "Invalid JSON format in " + path;
        return;
    }

    QJsonArray loginHistoryArray = doc.array();
    for (const QJsonValue& loginHistoryValue : loginHistoryArray) {
        if (!loginHistoryValue.isObject()) {
            qDebug() << "Invalid loginHistory data in " + path;
            continue;
        }

        QJsonObject loginHistoryObject = loginHistoryValue.toObject();
        QString username = loginHistoryObject["username"].toString();
        QString date = loginHistoryObject["date"].toString();
        QString time = loginHistoryObject["time"].toString();
        bool permitted = loginHistoryObject["permited_"].toBool();

        LoginHistory loginHistory(username, date, time, permitted);
        loginHistoryVector_.append(loginHistory);
    }
}

void LoginHistoryDatabase::handleRequestLoginHistory() {
    emit LoginHistoryResult(loginHistoryVector_);
}

void LoginHistoryDatabase::addLoginHistory(bool isMatch, const QString Date, const QString &currentTime, const QString &rfid) {
    LoginHistory newHistory(rfid, Date, currentTime, isMatch);
    // LoginHistory(QString username, QString date, QString time, bool permited = false);
    loginHistoryVector_.append(newHistory);
    qDebug() << "new History " << newHistory.getUsername() << " " << newHistory.getTime() << " " << newHistory.isPermitted();
}
