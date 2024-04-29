// cpssocket.cpp
#include "cpssocket.h"
#include <QJsonDocument>
#include <QJsonObject>

CPSSocket::CPSSocket(QObject *parent) : QObject(parent) {
    socket = new QTcpSocket(this);
    //QObject::connect(socket, &QTcpSocket::readyRead, this, &CPSSocket::collectingNewData);
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
                emit connectionChanged(true);
                QTextStream(stdout) << "kkkkkkkkkkkkkkkkkkkk";
                //collectingNewData();
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

    // Read the data from the socket
    QByteArray responseData = socket->readAll();

    // Parse the JSON data
    QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);
    if (!jsonDocument.isNull() && jsonDocument.isObject()) {
        QJsonObject jsonObject = jsonDocument.object();

        // Extract username, date, and time from the JSON object
        QString username = jsonObject["username"].toString();
        QString date = jsonObject["date"].toString();
        QString time = jsonObject["time"].toString();

        // Emit the newUser signal with the extracted username, date, and time
        emit newUser(username, date, time);
    } else {
        qDebug() << "Failed to parse JSON data";
    }
}
