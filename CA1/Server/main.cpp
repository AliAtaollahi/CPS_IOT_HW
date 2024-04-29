#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QCoreApplication>

class Server : public QTcpServer {
    Q_OBJECT
public:
    Server(QObject *parent = nullptr) : QTcpServer(parent) {}

protected:
    void incomingConnection(qintptr socketDescriptor) override {
        QTcpSocket *clientSocket = new QTcpSocket(this);
        if (!clientSocket->setSocketDescriptor(socketDescriptor)) {
            qDebug() << "Error setting socket descriptor";
            return;
        }

        qDebug() << "New connection from:" << clientSocket->peerAddress().toString();

        connect(clientSocket, &QTcpSocket::readyRead, this, [clientSocket]() {
            while (clientSocket->bytesAvailable()) {
                QByteArray data = clientSocket->readAll();
                qDebug() << "Received:" << data;
                clientSocket->write(data); // Echo back
            }
        });

        connect(clientSocket, &QTcpSocket::disconnected, this, [clientSocket]() {
            qDebug() << "Connection closed for:" << clientSocket->peerAddress().toString();
            clientSocket->deleteLater();
        });
    }
};

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    Server server;
    if (!server.listen(QHostAddress::LocalHost, 5050)) {
        qDebug() << "Server could not start!";
        return 1;
    }

    qDebug() << "Server started on port" << server.serverPort();
    return a.exec();
}
#include "main.moc"
