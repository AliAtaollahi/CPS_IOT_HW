// cpssocket.cpp
#include "cpssocket.h"

CPSSocket::CPSSocket(QObject *parent) : QObject(parent) {
    socket = new QTcpSocket(this);
}

void CPSSocket::connectToServer() {
    QTextStream(stdout) << "hello1" << Qt::endl;
    socket->connectToHost("127.0.0.1", 5050);
    QTextStream(stdout) << "hello2" << Qt::endl;
    if (socket->waitForConnected()) {
        QTextStream(stdout) << "hello3" << Qt::endl;
        qDebug() << "Connected to server.";
        socket->write("Hello server!");
    } else {
        QTextStream(stdout) << "hello4" << Qt::endl;
        qDebug() << "Failed to connect to server:" << socket->errorString();
    }
}
