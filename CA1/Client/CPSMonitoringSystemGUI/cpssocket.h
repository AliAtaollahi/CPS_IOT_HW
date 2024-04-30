// cpssocket.h
#ifndef CPSSOCKET_H
#define CPSSOCKET_H

#include <QObject>
#include <QTcpSocket>

class CPSSocket : public QObject {
    Q_OBJECT
public:
    explicit CPSSocket(QObject *parent = nullptr);
    QTcpSocket* getSocket() const;

public Q_SLOTS:
    void connectToServer(const QString &serverAddress, const QString &username, const QString &password);
    void collectingNewData();

private:
    QTcpSocket *socket;
    void ExtractNewUserData(const QJsonObject &jsonObject);

Q_SIGNALS:
    void newUser(const QString &username, const QString &date, const QString &time);
    void connectionChanged(bool enabled);
    void newHistory(const QJsonObject &jsonObject);
};

#endif // CPSSOCKET_H
