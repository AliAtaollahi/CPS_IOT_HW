#include <QCoreApplication>
#include "socketserver.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    SocketServer server;
    if (!server.listen(QHostAddress::LocalHost, 5050)) {
        qDebug() << "Server could not start!";
        return 1;
    }

    qDebug() << "Server started on port" << server.serverPort();
    return a.exec();
}
