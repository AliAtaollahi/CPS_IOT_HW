#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QCoreApplication>
#include <QDateTime>

class Server : public QTcpServer {
    Q_OBJECT
public:
    Server(QObject *parent = nullptr) : QTcpServer(parent) {
        // Initialize the set of hardcoded RFID values
        hardcodedRFIDs << "RFID1" << "RFID2" << "RFID3";
    }

    bool isValidRFID(const QString &rfid) {
        return hardcodedRFIDs.contains(rfid);
    }

protected:
    void incomingConnection(qintptr socketDescriptor) override {
        QTcpSocket *clientSocket = new QTcpSocket(this);
        if (!clientSocket->setSocketDescriptor(socketDescriptor)) {
            qDebug() << "Error setting socket descriptor";
            return;
        }

        qDebug() << "New connection from:" << clientSocket->peerAddress().toString();

        connect(clientSocket, &QTcpSocket::readyRead, this, [this, clientSocket]() {

        QByteArray data = clientSocket->readAll();
        qDebug() << "Received:" << data;
        processUserData(data, clientSocket);

        });

        connect(clientSocket, &QTcpSocket::disconnected, this, [clientSocket]() {
            qDebug() << "Connection closed for:" << clientSocket->peerAddress().toString();
            clientSocket->deleteLater();
        });
    }
private:
    QStringList hardcodedRFIDs;
    QTcpSocket* clientSocketpointer; // Store pointer to client socket

    void processUserData(const QByteArray &data, QTcpSocket *clientSocket) {
        QList<QByteArray> parts = data.split(':');
        if (parts.size() >= 2) {
            QString username = QString::fromUtf8(parts[0]);
            QString password = QString::fromUtf8(parts[1]);
            bool isValid = isValidUser(username, password);
            if (isValid) {
                qDebug() << "Access granted for:" << username;
                this->clientSocketpointer = clientSocket;
                clientSocket->write("Access granted\n");
            } else {
                qDebug() << "Access denied for:" << username;
                clientSocket->write("Access denied\n");
                clientSocket->close();
            }
            qDebug() << "Username:" << username << "Password:" << password;
        } else {
            qDebug() << "Invalid message format";
        }
    }

    bool isValidUser(const QString &username, const QString &password) {
        return (username == "test" && password == "1234");
    }

    void sendWebSocketMessage(const QString &rfid) {
        // Construct message with RFID and date/time
        // Get current date and time
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString dateTimeString = currentDateTime.toString("yyyy-MM-dd HH:mm:ss");

        // Construct message with RFID and date/time
        QString message = QString("RFID: %1, Date/Time: %2").arg(rfid).arg(dateTimeString);

        QByteArray data = message.toUtf8();

        // Write the data to the socket
        qint64 bytesWritten = clientSocketpointer->write(data);

        if (bytesWritten == -1) {
            // Error handling: failed to write data
            qDebug() << "Failed to write data to socket:" << clientSocketpointer->errorString();
        } else {
            qDebug() << "WebSocket message sent to client:" << message;
        }

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
