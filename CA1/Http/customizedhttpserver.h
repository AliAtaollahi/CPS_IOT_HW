#ifndef CUSTOMIZEDHTTPSERVER_H
#define CUSTOMIZEDHTTPSERVER_H

#include <QObject>
#include <QCoreApplication>
#include <QHttpServer>
#include <QHttpServerRequest>
#include <QHttpServerResponse>
#include <QJsonDocument>
#include <QJsonObject>

class CustomizedHttpServer : public QObject
{
    Q_OBJECT
public:
    explicit CustomizedHttpServer(QObject *parent = nullptr);

private:
    QHttpServer *http_server;

signals:

private slots:
    QHttpServerResponse handleRequest(const QHttpServerRequest &request);
};

#endif // CUSTOMIZEDHTTPSERVER_H
