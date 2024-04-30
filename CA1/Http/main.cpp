#include "customizedhttpserver.h"

#include <QCoreApplication>
#include <QHttpServer>
#include <QHttpServerRequest>
#include <QHttpServerResponse>
#include <QJsonDocument>
#include <QJsonObject>



int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    CustomizedHttpServer customized_http_server = CustomizedHttpServer();

    qInfo("Server running on port 80");
    return app.exec();
}
