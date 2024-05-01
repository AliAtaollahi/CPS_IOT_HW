#include "authenticator.h"
#include <QDebug>

Authenticator::Authenticator(QObject *parent) : QObject(parent)
{
}

void Authenticator::authenticateUser(const QByteArray &data, QTcpSocket *clientSocket)
{
    QList<QByteArray> parts = data.split(':');

    if (parts.size() >= 2) {
        QString username = QString::fromUtf8(parts[0]);
        QString password = QString::fromUtf8(parts[1]);
        bool isValid = isValidUser(username, password);
        if (isValid) {
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

bool Authenticator::isValidUser(const QString &username, const QString &password)
{
    return (username == "test" && password == "1234");
}
