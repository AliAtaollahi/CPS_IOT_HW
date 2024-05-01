#include <QCoreApplication>
#include "loginhistorydatabase.h"
#include "socketserver.h"
#include "customizedhttpserver.h"

const QString USERS_FILE_PATH = "../../data/employees.json";
const QString ADMINS_FILE_PATH = "../../data/admins.json";
const QString HISTORY_FILE_PATH = "../../data/history.json";
const int HTTP_SERVER_PORT = 80;
const int WEB_SOCKET_PORT = 5050;

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    CustomizedHttpServer customizedHttpServer = CustomizedHttpServer(HTTP_SERVER_PORT, USERS_FILE_PATH);
    qDebug() << "Server running on port " << HTTP_SERVER_PORT;

    SocketServer server;
    if (!server.listen(QHostAddress::LocalHost, WEB_SOCKET_PORT)) {
        qDebug() << "Server could not start!";
        return 1;
    }
    qDebug() << "Server started on port" << server.serverPort();

    LoginHistoryDatabase loginHistoryDatabase(HISTORY_FILE_PATH);

    QObject::connect(&customizedHttpServer, &CustomizedHttpServer::resultRfidCheck, &server, &SocketServer::sendNewUserDataToAdmin);
    QObject::connect(&customizedHttpServer, &CustomizedHttpServer::resultRfidCheckHistory, &loginHistoryDatabase, &LoginHistoryDatabase::addLoginHistory);

    QObject::connect(&server, &SocketServer::requestLoginHistory, &loginHistoryDatabase, &LoginHistoryDatabase::handleRequestLoginHistory);
    QObject::connect(&loginHistoryDatabase, &LoginHistoryDatabase::loginHistoryResult, &server, &SocketServer::SendLoginHistoryResult);

    return a.exec();
}
