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
        processData(data, clientSocket);
        clientSocketpointer = clientSocket;

    });

    connect(clientSocket, &QTcpSocket::disconnected, this, [clientSocket]() {
        qDebug() << "Connection closed for:" << clientSocket->peerAddress().toString();
        clientSocket->deleteLater();
    });
}

bool SocketServer::isValidRFID(const QString &rfid) {
    return hardcodedRFIDs.contains(rfid);
}

void SocketServer::processData(QByteArray &data, QTcpSocket *clientSocket) {
    qDebug() << "in  SocketServer::processData";
    if(data == "historyRequest"){
        emit requestLoginHistory();
    }
    else{
        authenticateUser(data, clientSocket);
    }
}

void SocketServer::authenticateUser(const QByteArray &data, QTcpSocket *clientSocket){
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

bool SocketServer::isValidUser(const QString &username, const QString &password) {
    return (username == "test" && password == "1234");
}

void SocketServer::sendNewUserDataToAdmin(bool isMatch, const QString &rfid) {

    QDateTime currentDateTime = QDateTime::currentDateTime();

    QDate currentDate = currentDateTime.date();
    QTime currentTime = currentDateTime.time();

    QString dateString = currentDate.toString("yyyy-MM-dd");
    QString timeString = currentTime.toString("HH:mm:ss");

    QJsonObject messageObj;
    messageObj["type"] = "user";
    messageObj["username"] = rfid;
    messageObj["date"] = dateString;
    messageObj["time"] = timeString;

    QJsonDocument jsonDocument(messageObj);

    QByteArray jsonData = jsonDocument.toJson();

    qint64 bytesWritten = clientSocketpointer->write(jsonData);

    if (bytesWritten == -1) {
        qDebug() << "Failed to write data to socket:" << clientSocketpointer->errorString();
    } else {
        qDebug() << "WebSocket message sent to client:" << jsonData;
    }
}


void SocketServer::SendLoginHistoryResult(const QVector<LoginHistory> &loginHistories){
    if (this->clientSocketpointer) {
        QJsonArray dataArray;

        for (const LoginHistory &entry : loginHistories) {
            QJsonObject obj;
            obj["username"] = entry.getUsername();
            obj["date"] = entry.getDate();
            obj["time"] = entry.getTime();
            obj["permitted"] = entry.isPermitted();
            dataArray.append(obj);
        }
        QJsonObject mainObj;
        mainObj["type"] = "history";
        mainObj["data"] = dataArray;

        // Convert the main JSON object to a JSON document
        QJsonDocument jsonDocument(mainObj);

        // Convert the JSON document to a QByteArray
        QByteArray jsonData = jsonDocument.toJson();
        clientSocketpointer->write(jsonData);
    }
}
