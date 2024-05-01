#include "loginhistorydatabase.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

LoginHistoryDatabase::LoginHistoryDatabase(const QString &initialDataPath, QObject *parent)
    : QObject(parent)
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

    loginHistoryVector_ = parseLoginHistories(jsonData);
}

QVector<LoginHistory> LoginHistoryDatabase::parseLoginHistories(const QByteArray &jsonData)
{
    QVector<LoginHistory> histories;

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (!doc.isArray()) {
        qDebug() << "Invalid JSON format";
        return histories;
    }

    QJsonArray loginHistoryArray = doc.array();
    for (const QJsonValue& loginHistoryValue : loginHistoryArray) {
        if (!loginHistoryValue.isObject()) {
            qDebug() << "Invalid loginHistory data";
            continue;
        }

        QJsonObject loginHistoryObject = loginHistoryValue.toObject();
        LoginHistory loginHistory = parseLoginHistory(loginHistoryObject);
        histories.append(loginHistory);
    }

    return histories;
}

LoginHistory LoginHistoryDatabase::parseLoginHistory(const QJsonObject &loginHistoryObject)
{
    QString username = loginHistoryObject["username"].toString();
    QString date = loginHistoryObject["date"].toString();
    QString time = loginHistoryObject["time"].toString();
    bool permitted = loginHistoryObject["permited_"].toBool();

    return LoginHistory(username, date, time, permitted);
}

void LoginHistoryDatabase::handleRequestLoginHistory()
{
    emit loginHistoryResult(loginHistoryVector_);
}

void LoginHistoryDatabase::addLoginHistory(bool isMatch, const QString &date, const QString &time, const QString &rfid)
{
    LoginHistory newHistory(rfid, date, time, isMatch);
    loginHistoryVector_.append(newHistory);
    qDebug() << "New history added: " << newHistory.getUsername() << " " << newHistory.getTime() << " " << newHistory.isPermitted();
}
