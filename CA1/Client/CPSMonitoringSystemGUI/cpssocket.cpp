// cpssocket.cpp
#include "cpssocket.h"
#include <QJsonDocument>
#include <QJsonObject>

CPSSocket::CPSSocket(QObject *parent) : QObject(parent) {
    socket = new QTcpSocket(this);
    //QObject::connect(socket, &QTcpSocket::readyRead, this, &CPSSocket::collectingNewData);
}

QTcpSocket* CPSSocket::getSocket() const {
    return socket;
}

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

            if(responseData == "1")
            {
                emit connectionChanged(false);
                QTextStream(stdout) << "kkkkkkkkkkkkkkkkkkkk";
                QObject::connect(socket, &QTcpSocket::readyRead, this, &CPSSocket::collectingNewData);
                QTextStream(stdout) << "pppppppppppppppppppppppppppp";

            }
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


void CPSSocket::collectingNewData() {

    QTextStream(stdout) << "uuuuuuuuuuuuuuuuuuuuuuuuuuuu";

    QByteArray responseData = socket->readAll();

    QTextStream(stdout) << responseData;
    // Parse the JSON data
    QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);
    if (!jsonDocument.isNull() && jsonDocument.isObject()) {
        QJsonObject jsonObject = jsonDocument.object();

        // Check the type field
        if (jsonObject.contains("type") && jsonObject["type"].toString() == "user") {
           ExtractNewUserData(jsonObject);
        } else if (jsonObject.contains("type") && jsonObject["type"].toString() == "history") {
            QTextStream(stdout) << "helloooooooooooooooooooo";
           emit newHistory(jsonObject);
        } else {
            qDebug() << "Invalid type field in JSON data";
        }
    } else {
        qDebug() << "Failed to parse JSON data";
    }
}

void CPSSocket::ExtractNewUserData(const QJsonObject &jsonObject) {

    QString username = jsonObject["username"].toString();
    QString date = jsonObject["date"].toString();
    QString time = jsonObject["time"].toString();

    emit newUser(username, date, time);
}
