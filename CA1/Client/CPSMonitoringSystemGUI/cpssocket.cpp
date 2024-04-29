// cpssocket.cpp
#include "cpssocket.h"

CPSSocket::CPSSocket(QObject *parent) : QObject(parent) {
    socket = new QTcpSocket(this);
}

/*void CPSSocket::connectToServer() {
    socket->connectToHost("127.0.0.1", 5050);
    QTextStream(stdout) << "hello2" << Qt::endl;
    if (socket->waitForConnected()) {

        qDebug() << "Connected to server.";
        socket->write("Hello server!");
    } else {

        qDebug() << "Failed to connect to server:" << socket->errorString();
    }


}*/

void CPSSocket::connectToServer(const QString &serverAddress, const QString &username, const QString &password) {
    // Connect to the server
    socket->connectToHost(serverAddress, 5050);
    QTextStream(stdout) << "hello2" << Qt::endl;
    QTextStream(stdout) << username <<password << Qt::endl;
    if (socket->waitForConnected()) {
        QTextStream(stdout) << "hello3" << Qt::endl;
        // Connection successful, prepare the message
        QString message = username + ":" + password;

        // Send the message to the server
        qDebug() << "Connected to server. Sending message: " << message;
        socket->write(message.toUtf8());
    } else {
        QTextStream(stdout) << "hello4" << Qt::endl;
        // Connection failed
        qDebug() << "Failed to connect to server:" << socket->errorString();
    }
}
