// cpssocket.cpp
#include "cpssocket.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

CPSSocket::CPSSocket(QObject *parent) : QObject(parent) {
    socket = new QTcpSocket(this);
}

QTcpSocket* CPSSocket::getSocket() const {
    return socket;
}

void CPSSocket::connectToServer(const QString &serverAddress, const QString &username, const QString &password) {

    socket->connectToHost(serverAddress, 5050);

    if (socket->waitForConnected()) {

        QString message = username + ":" + password;
        QTextStream(stdout) << "Connected to server. Sending message: " << message << Qt::endl;
        socket->write(message.toUtf8());

        if (socket->waitForReadyRead()) {

            QByteArray responseData = socket->readAll();
            QTextStream(stdout) << "Received response from server:" << responseData << Qt::endl;

            if(responseData == "1")//if it is verfied
            {
                emit connectionChanged(false);
                QObject::connect(socket, &QTcpSocket::readyRead, this, &CPSSocket::collectingNewData);
            }
        } else {
            QTextStream(stdout) << "Timeout while waiting for server response" << Qt::endl;
        }
    } else {
        QTextStream(stdout) << "Failed to connect to server:" << socket->errorString() << Qt::endl;
    }
}


void CPSSocket::collectingNewData() {

    QByteArray responseData = socket->readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);

    if (!jsonDocument.isNull() && jsonDocument.isObject()) {
        QJsonObject jsonObject = jsonDocument.object();
        if (jsonObject.contains("type") && jsonObject["type"].toString() == "user") {
           ExtractNewUserData(jsonObject);
        } else if (jsonObject.contains("type") && jsonObject["type"].toString() == "history") {
           emit newHistory(jsonObject);
        } else {
            QTextStream(stdout) << "Invalid type field in JSON data" << Qt::endl;
        }
    } else {
        QTextStream(stdout) << "Failed to parse JSON data" << Qt::endl;
    }
}

void CPSSocket::ExtractNewUserData(const QJsonObject &jsonObject) {
    QString username = jsonObject["username"].toString();
    QString date = jsonObject["date"].toString();
    QString time = jsonObject["time"].toString();
    emit newUser(username, date, time);
}
