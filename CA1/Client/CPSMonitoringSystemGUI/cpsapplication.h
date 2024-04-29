#ifndef CPSAPPLICATION_H
#define CPSAPPLICATION_H

#include <QObject>
#include <QApplication>

#include "cpsmainwindow.h"
#include "cpshistorywindow.h"
#include "cpswindowsapitools.h"

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

private: // methods

private: // members
    MainWindow    *_window;
    HistoryWindow *_history;

    //TODO:
    //YourSocketClass *_YourSocketClassInstance;
};

} // end of CPS

#endif // CPSAPPLICATION_H
