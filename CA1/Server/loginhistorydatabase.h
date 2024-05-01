#ifndef LOGINHISTORYDATABASE_H
#define LOGINHISTORYDATABASE_H

#include <QObject>
#include <QVector>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include "loginhistory.h"

class LoginHistoryDatabase : public QObject
{
    Q_OBJECT
public:
    explicit LoginHistoryDatabase(const QString &initialDataPath, QObject *parent = nullptr);

    const QVector<LoginHistory>& getLoginHistoriesVector() const;

signals:
    void LoginHistoryResult(const QVector<LoginHistory> &history);

public slots:
    void handleRequestLoginHistory();
    void addLoginHistory(bool isMatch, const QString Date, const QString &currentTime, const QString &rfid);

private:
    QVector<LoginHistory> loginHistoryVector_;

    void readLoginHistoriesFromJson(const QString &path);
};

#endif // LOGINHISTORYDATABASE_H
