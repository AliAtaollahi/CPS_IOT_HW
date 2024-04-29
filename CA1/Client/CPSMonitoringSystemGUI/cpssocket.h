// cpssocket.h
#ifndef CPSSOCKET_H
#define CPSSOCKET_H

#include <QObject>
#include <QTcpSocket>

class CPSSocket : public QObject {
    Q_OBJECT
public:
    explicit CPSSocket(QObject *parent = nullptr);

public slots:
    void connectToServer(const QString &serverAddress, const QString &username, const QString &password);

private:
    QTcpSocket *socket;
};

#endif // CPSSOCKET_H
