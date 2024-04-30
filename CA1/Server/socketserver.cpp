#include "socketserver.h"

SocketServer::SocketServer(QObject *parent) : QTcpServer(parent) {
    hardcodedRFIDs << "RFID1" << "RFID2" << "RFID3";
}

void SocketServer::incomingConnection(qintptr socketDescriptor) {
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

bool SocketServer::isValidRFID(const QString &rfid) {
    return hardcodedRFIDs.contains(rfid);
}

void SocketServer::processUserData(const QByteArray &data, QTcpSocket *clientSocket) {
    if(data == "historyRequest"){

        qDebug() << "i am in historyRequest.";
        // Create the JSON array for the data
        QJsonArray dataArray;

        // Create the first JSON object
        QJsonObject obj1;
        obj1["username"] = "user1";
        obj1["date"] = "2024-04-30";
        obj1["time"] = "10:00";

        // Create the second JSON object
        QJsonObject obj2;
        obj2["username"] = "user2";
        obj2["date"] = "2024-04-30";
        obj2["time"] = "11:30";

        // Add the JSON objects to the data array
        dataArray.append(obj1);
        dataArray.append(obj2);

        // Create the main JSON object
        QJsonObject mainObj;
        mainObj["type"] = "history"; // Add the "type" field
        mainObj["data"] = dataArray; // Add the "data" field with the array

        // Convert the main JSON object to a JSON document
        QJsonDocument jsonDocument(mainObj);

        // Convert the JSON document to a QByteArray
        QByteArray jsonData = jsonDocument.toJson();

        qDebug() << "i am still in historyRequest.";
        clientSocket->write(jsonData);
        qDebug() << "i have sent message in historyRequest.";
    }
    else{
        QList<QByteArray> parts = data.split(':');

        if (parts.size() >= 2) {
            QString username = QString::fromUtf8(parts[0]);
            QString password = QString::fromUtf8(parts[1]);
            bool isValid = isValidUser(username, password);
            if (isValid) {

                //this->clientSocketpointer = clientSocket;
                clientSocket->write("1");
                qDebug() << "Access granted for:" << username;
            } else {
                qDebug() << "Access denied for:" << username;
                clientSocket->write("0");
                clientSocket->close();
            }
            qDebug() << "Username:" << username << "Password:" << password;
        } else {
            qDebug() << "Invalid message format";
        }
    }
}

bool SocketServer::isValidUser(const QString &username, const QString &password) {
    return (username == "test" && password == "1234");
}

void SocketServer::sendWebSocketMessage(const QString &rfid) {
    // Construct message with RFID and date/time
    // Get current date and time
    QDateTime currentDateTime = QDateTime::currentDateTime();

    // Extract date and time separately
    QDate currentDate = currentDateTime.date();
    QTime currentTime = currentDateTime.time();

    // Convert date and time to strings
    QString dateString = currentDate.toString("yyyy-MM-dd");
    QString timeString = currentTime.toString("HH:mm:ss");

    QJsonObject messageObj;
    messageObj["username"] = rfid;
    messageObj["date"] = dateString;
    messageObj["time"] = timeString;

    QJsonDocument jsonDocument(messageObj);

    // Convert the JSON document to a QByteArray
    QByteArray jsonData = jsonDocument.toJson();


    // Write the data to the socket
    qint64 bytesWritten = clientSocketpointer->write(jsonData);

    if (bytesWritten == -1) {
        // Error handling: failed to write data
        qDebug() << "Failed to write data to socket:" << clientSocketpointer->errorString();
    } else {
        qDebug() << "WebSocket message sent to client:" << jsonData;
    }
}
