#ifndef CPSHISTORYWINDOW_H
#define CPSHISTORYWINDOW_H

#include <QWidget>
#include <QListWidget>
#include <QJsonArray>
#include <QJsonObject>

namespace CPS {

class HistoryWindow : public QWidget
{
    Q_OBJECT
public:
    explicit HistoryWindow(QWidget *parent = nullptr);
    ~HistoryWindow();

    void show(const QJsonArray &array);

private:
    void closeEvent(QCloseEvent * event) override;

private:
    QListWidget *_list;
};

} // end of CPS

#endif // CPSHISTORYWINDOW_H
