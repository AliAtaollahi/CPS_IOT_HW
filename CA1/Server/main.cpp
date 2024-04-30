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
                // Split the message using ':'
                QList<QByteArray> parts = data.split(':');

                // Check if there are at least two parts
                if (parts.size() >= 2) {
                    // Extract the username and password
                    QString username = QString::fromUtf8(parts[0]);
                    QString password = QString::fromUtf8(parts[1]);

                    // Check if the username and password match the fixed strings
                    if (username == "test" && password == "1234") {
                        qDebug() << "Access granted for:" << username;
                        clientSocket->write("Access granted\n"); // Send a message indicating access granted
                        // Process further actions for authenticated client
                    } else {
                        qDebug() << "Access denied for:" << username;
                        clientSocket->write("Access denied\n"); // Send a message indicating access denied
                        clientSocket->close(); // Close the connection
                    }

                    // Do something with the username and password
                    qDebug() << "Username:" << username << "Password:" << password;
                } else {
                    qDebug() << "Invalid message format";
                }
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
