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
        QTextStream(stdout) << "Connected to server. Sending message: " << message << Qt::endl;
        socket->write(message.toUtf8());
        if (socket->waitForReadyRead()) {
            // Read the response from the server
            QByteArray responseData = socket->readAll();
            QTextStream(stdout) << "Received response from server:" << responseData << Qt::endl;
            // Process the response as needed
        } else {
            // Failed to receive response within the timeout
            QTextStream(stdout) << "Timeout while waiting for server response" << Qt::endl;
        }
    } else {
        QTextStream(stdout) << "hello4" << Qt::endl;
        // Connection failed
        QTextStream(stdout) << "Failed to connect to server:" << socket->errorString() << Qt::endl;
    }
}
