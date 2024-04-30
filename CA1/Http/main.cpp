#include "customizedhttpserver.h"

#include <QCoreApplication>
#include <QHttpServer>
#include <QHttpServerRequest>
#include <QHttpServerResponse>
#include <QJsonDocument>
#include <QJsonObject>

const QString USERS_FILE_PATH = "../../data/employee_info.json";
const QString ADMINS_FILE_PATH = "../../data/admins_info.json";
const QString HISTORY_FILE_PATH = "../../data/history_info.json";
const int HTTP_SERVER_PORT = 8080;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    CustomizedHttpServer customizedHttpServer = CustomizedHttpServer(HTTP_SERVER_PORT, USERS_FILE_PATH);
    

    qInfo("Server running on port 8080");
    return app.exec();
}
