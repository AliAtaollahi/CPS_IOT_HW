#ifndef LOGINHISTORYDATABASE_H
#define LOGINHISTORYDATABASE_H

#include <QObject>
#include <QVector>
#include "loginhistory.h"

class LoginHistoryDatabase : public QObject
{
    Q_OBJECT
public:
    explicit LoginHistoryDatabase(const QString &initialDataPath, QObject *parent = nullptr);

    const QVector<LoginHistory>& getLoginHistoriesVector() const;

signals:
    void loginHistoryResult(const QVector<LoginHistory> &history);

public slots:
    void handleRequestLoginHistory();
    void addLoginHistory(bool isMatch, const QString &date, const QString &time, const QString &rfid);

private:
    QVector<LoginHistory> loginHistoryVector_;

    void readLoginHistoriesFromJson(const QString &path);
    QVector<LoginHistory> parseLoginHistories(const QByteArray &jsonData);
    LoginHistory parseLoginHistory(const QJsonObject &loginHistoryObject);
};

#endif // LOGINHISTORYDATABASE_H
