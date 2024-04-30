#ifndef CPSAPPLICATION_H
#define CPSAPPLICATION_H

#include <QObject>
#include <QApplication>

#include "cpsmainwindow.h"
#include "cpshistorywindow.h"
#include "cpswindowsapitools.h"
#include "cpssocket.h"

namespace CPS {

class Application : public QObject
{
    Q_OBJECT

public:

    explicit Application(QObject *parent = nullptr);
    ~Application();

    void show();

Q_SIGNALS:


private Q_SLOTS:
    void showHistoryWindow();
    void connectToServer(const QString &serverAddress, const QString &username, const QString &password);

   // void connectToServer();

private: // methods

private: // members
    MainWindow    *_window;
    HistoryWindow *_history;
    CPSSocket *_socket; // Instance of the socket class

    //TODO:
    //YourSocketClass *_YourSocketClassInstance;
};

} // end of CPS

#endif // CPSAPPLICATION_H
