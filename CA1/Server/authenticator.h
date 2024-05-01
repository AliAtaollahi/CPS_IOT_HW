#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include <QObject>
#include <QString>
#include <QTcpSocket>

class Authenticator : public QObject
{
    Q_OBJECT
public:
    explicit Authenticator(QObject *parent = nullptr);

    void authenticateUser(const QByteArray &data, QTcpSocket *clientSocket);

private:
    bool isValidUser(const QString &username, const QString &password);
};

#endif // AUTHENTICATOR_H
