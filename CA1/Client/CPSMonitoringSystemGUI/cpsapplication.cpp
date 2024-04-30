#include "cpsapplication.h"

#include <QTextStream>

namespace CPS {

Application::Application(QObject *parent)
    : QObject{parent},
    _window(new MainWindow),
    _history(new HistoryWindow),
    _socket(new CPSSocket) // Instantiate the socket here
{
    setWindowsThemeToDark<MainWindow>(*_window);

    QObject::connect(_window, &MainWindow::historyuBtnClicked, this, &Application::sendHistoryRequest);

    QObject::connect(_window, &MainWindow::connectBtnClicked, this, &Application::connectToServer); // Connect button click to server connection



    // TODO:
    QObject::connect(_socket, &CPSSocket::newUser, _window, &MainWindow::showUserDetails);
    QObject::connect(_socket, &CPSSocket::newHistory, this, &Application::showHistoryWindow);///
    QObject::connect(_socket, &CPSSocket::connectionChanged, _window, &MainWindow::changeRightPanelEnabled);

}

Application::~Application()
{
    delete this->_window;
    delete this->_history;

    //TODO:
    //delete this->_YourSocketClassInstance;
    delete this-> _socket;
}

void Application::show()
{
    this->_window->show();
}

void Application::showHistoryWindow(const QJsonObject &jsonObject)
{
    QTextStream(stdout) << "hello" << Qt::endl;
    setWindowsThemeToDark<HistoryWindow>(*_history);

    QJsonArray historyArray = jsonObject["data"].toArray();

    QVariantList list;

    for (const QJsonValue &value : historyArray) {
        QJsonObject historyObject = value.toObject();
        QJsonObject obj;
        obj["username"] = historyObject["username"].toString();
        obj["date"] = historyObject["date"].toString();
        obj["time"] = historyObject["time"].toString();
        list.append(obj);

    }

    QJsonArray data = QJsonArray::fromVariantList(list);





    // TODO:
    /*
         * fetch data from server and show it in history window.
         * your data must be in QJsonArray format.
         * something like this:
         *
         * [
         *     {
         *          username: string,
         *          date: string,
         *          time: string,
         *     },
         *
         *     {
         *          username: string,
         *          date: string,
         *          time: string,
         *     }
         * ]
         *
         *  below is an example of how to create a QJsonArray from QVariantList: (beginer level)
         *  please erase this horrible example and implement your own logic.
         *  you must fetch a json from server
         *
         * */


    _history->show(data);
}


void Application::sendHistoryRequest(){
    QString message = "historyRequest";
    _socket->getSocket()->write(message.toUtf8());
}


void Application::connectToServer(const QString &serverAddress, const QString &username, const QString &password) {
    // When the "اتصال به سرور" button is clicked, connect to server using the socket
    QTextStream(stdout) << "hello" << Qt::endl;
    _socket->connectToServer(serverAddress, username, password);
}

} // end of CPS
