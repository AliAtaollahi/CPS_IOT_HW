#ifndef CUSTOMIZEDHTTPSERVER_H
#define CUSTOMIZEDHTTPSERVER_H

#include <QObject>
#include <QCoreApplication>
#include <QHttpServer>
#include <QHttpServerRequest>
#include <QHttpServerResponse>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonObject>
#include "employeesdatabase.h"

class CustomizedHttpServer : public QObject
{
    Q_OBJECT
public:
    explicit CustomizedHttpServer(int port, const QString &initialDataPath, QObject *parent = nullptr);
    bool startServer(int port);

signals:
    void resultRfidCheck(bool isMatch, const QDateTime &currentTime, const QString &rfid);

private slots:
    QHttpServerResponse handleRequest(const QHttpServerRequest &request);

private:
    QHttpServer* httpServer_;
    EmployeesDatabase employeesDatabase_;
};

#endif // CUSTOMIZEDHTTPSERVER_H
