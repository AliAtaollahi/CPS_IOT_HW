#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDateTime>

class SocketServer : public QTcpServer {
    Q_OBJECT

public:
    SocketServer(QObject *parent = nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor) override;
    bool isValidRFID(const QString &rfid);
    void processData(QByteArray &data, QTcpSocket *clientSocket);
    bool isValidUser(const QString &username, const QString &password);
    void sendNewUserDataToAdmin(const QString &rfid);
    QByteArray retrieveHistoryData();
    void authenticateUser(const QByteArray &data, QTcpSocket *clientSocket);

private:
    QStringList hardcodedRFIDs;
    QTcpSocket* clientSocketpointer; // Store pointer to client socket
};

#endif // SOCKETSERVER_H
