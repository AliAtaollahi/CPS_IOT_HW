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
    void collectingNewData(); // Method to collect new data

private:
    QTcpSocket *socket;

signals:
    void newUser(const QString &username, const QString &date, const QString &time);
    void connectionChanged(bool enabled);


};

#endif // CPSSOCKET_H
