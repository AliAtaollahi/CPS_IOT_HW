#ifndef CPSMAINWINDOW_H
#define CPSMAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>

#include "cpstextfield.h"
#include "cpsbutton.h"
#include "cpslabel.h"

namespace CPS {

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setTime(const QString& time);
    void setDate(const QString& date);
    void setUsername(const QString& username);

Q_SIGNALS:
    void historyuBtnClicked();
    void connectBtnClicked(const QString &address, const QString &username, const QString &password);

public Q_SLOTS:
    void changeRightPanelEnabled(bool enabled);
    void showUserDetails(const QString &username, const QString &date, const QString &time);

private: // methods
    void setupConnections();
    void setupGlobalStyle();
    void setupWindowLayout();
    void setupHeader();
    void setupRightPanel();
    void setupLeftPanel();
    void closeEvent(QCloseEvent *event) override;

private: // members
    Button      *_connectBtn;
    TextField   *_addressInput;
    TextField   *_usernameInput;
    TextField   *_passwordInput;

    Label       *_date;
    Label       *_time;
    Label       *_username;
    Button      *_historyBtn;

    QVBoxLayout *_leftPanel;
    QHBoxLayout *_mainLayout;
    QVBoxLayout *_rightPanel;

    const int _windowMargin = 30;
};

} // end of CPS

#endif // CPSMAINWINDOW_H
