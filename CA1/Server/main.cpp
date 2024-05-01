#include <QCoreApplication>
#include "socketserver.h"
#include "customizedhttpserver.h"

const QString USERS_FILE_PATH = "../../data/employees.json";
const QString ADMINS_FILE_PATH = "../../data/admins.json";
const QString HISTORY_FILE_PATH = "../../data/history.json";
const int HTTP_SERVER_PORT = 80;

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    CustomizedHttpServer customizedHttpServer = CustomizedHttpServer(HTTP_SERVER_PORT, USERS_FILE_PATH);
    qInfo("Server running on port 80");

    SocketServer server;
    if (!server.listen(QHostAddress::LocalHost, 5050)) {
        qDebug() << "Server could not start!";
        return 1;
    }
    qDebug() << "Server started on port" << server.serverPort();

    return a.exec();
}
