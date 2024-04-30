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
const int HTTP_SERVER_PORT = 4321;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    CustomizedHttpServer customizedHttpServer = CustomizedHttpServer(HTTP_SERVER_PORT, USERS_FILE_PATH);
    

    qInfo("Server running on port 80");
    return app.exec();
}
