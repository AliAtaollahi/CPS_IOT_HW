#include "cpshistorywindow.h"
#include <QCloseEvent>

namespace CPS {

HistoryWindow::HistoryWindow(QWidget *parent)
    : QWidget{parent},
    _list(new QListWidget(this))
{
    this->setMinimumSize({720, 480});
    this->setMaximumSize({720, 480});
    this->setBackgroundRole(QPalette::Dark);
    this->setWindowIcon(QIcon("Ut.ico"));
    this->setWindowFlag(Qt::CustomizeWindowHint);
    this->setWindowTitle("IoT Monitoring System - History");
    this->setPalette(QPalette(QColor::fromString("#E0E0E0"), QColor::fromString("#121212")));

    int x = 20, y = 20;
    int width = this->width() - 40;
    int height = this->height() - 40;

    _list->setGeometry(x, y, width,  height);
}

HistoryWindow::~HistoryWindow()
{
    delete _list;
}

void HistoryWindow::show(const QJsonArray &array)
{
    uint index = 0;
    _list->addItem("index\tusername\t|\tdate\t|\ttime");

    for (auto& item : array){
        index++;

        auto object       = item.toObject();
        auto structure    = QString("%1-\t%2\t|\t%3\t|\t%4");

        auto username     = object["username"].toString();
        auto date         = object["date"].toString();
        auto time         = object["time"].toString();

        auto entry        = structure.arg(QString::number(index), username, date, time);

        _list->addItem(entry);
    }

    QWidget::show();
}

void HistoryWindow::closeEvent(QCloseEvent *event)
{
    _list->clear();
    event->accept();
}

} // end of CPS
