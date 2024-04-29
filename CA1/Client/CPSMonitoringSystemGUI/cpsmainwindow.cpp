#include "cpsmainwindow.h"
#include <QCloseEvent>

namespace CPS {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    _addressInput(new TextField("آدرس سوکت سرور", this)),
    _usernameInput(new TextField("نام کاربری", this)),
    _passwordInput(new TextField("رمز عبور", this)),
    _connectBtn(new Button("اتصال به سرور", this)),

    _username(new Label("شناسه کاربری:  __________", this)),
    _date(new Label("تاریخ:  __ / __ / ____", this)),
    _time(new Label("ساعت:  __ : __", this)),
    _historyBtn(new Button("نمایش تاریخچه", this)),

    _mainLayout(new QHBoxLayout(this)),
    _rightPanel( new QVBoxLayout(this)),
    _leftPanel(new QVBoxLayout(this))
{
    this->setupConnections();
    this->setupGlobalStyle();
    this->setupWindowLayout();
    this->setupHeader();
    this->setupRightPanel();
    this->setupLeftPanel();
}

MainWindow::~MainWindow() {
    delete this->_connectBtn;
    delete this->_addressInput;
    delete this->_usernameInput;
    delete this->_passwordInput;
    delete this->_username;
    delete this->_date;
    delete this->_time;
    delete this->_historyBtn;
    delete this->_mainLayout;
    delete this->_rightPanel;
    delete this->_leftPanel;
}

/*
 * =============================================
 * ================== PUBLICS ==================
 * =============================================
 */

void MainWindow::setTime(const QString &time)
{
    _time->setText(QString("ساعت: %1").arg(time));
}

void MainWindow::setDate(const QString &date)
{
    _date->setText(QString("تاریخ: %1").arg(date));
}

void MainWindow::setUsername(const QString &username)
{
    _username->setText(QString("شناسه کاربری: %1").arg(username));
}


/*
 * =============================================
 * =================== SLOTS ===================
 * =============================================
 */

void MainWindow::changeRightPanelEnabled(bool enabled)
{
    _rightPanel->setEnabled(enabled);
}

void MainWindow::showUserDetails(const QString &username, const QString &date, const QString &time)
{
    this->setDate(date);
    this->setTime(time);
    this->setUsername(username);
}


/*
 * =============================================
 * ================== PRIVATES =================
 * =============================================
 */

void MainWindow::setupConnections()
{
    auto connectFn = [this] () {
        Q_EMIT connectBtnClicked(_addressInput->text(),
                                 _usernameInput->text(),
                                 _passwordInput->text());
    };

    connect(_connectBtn, &QPushButton::clicked, connectFn);
    connect(_historyBtn, &QPushButton::clicked, this, &MainWindow::historyuBtnClicked);
}

void MainWindow::setupGlobalStyle()
{
    this->setMinimumSize({720, 480});
    this->setMaximumSize({720, 480});
    this->setBackgroundRole(QPalette::Dark);
    this->setWindowIcon(QIcon("Ut.ico"));
    this->setWindowFlag(Qt::CustomizeWindowHint);
    this->setWindowTitle("IoT Monitoring System");
    this->setPalette(QPalette(QColor::fromString("#E0E0E0"), QColor::fromString("#121212")));
}

void MainWindow::setupWindowLayout()
{
    _mainLayout->addLayout(_rightPanel);
    _mainLayout->addLayout(_leftPanel);
}

void MainWindow::setupHeader()
{
    QFont font;
    font.setPixelSize(25);
    font.setBold(true);

    QLabel *headingLbl = new QLabel(this);
    headingLbl->setFont(font);
    headingLbl->setMargin(20);
    headingLbl->setAlignment(Qt::AlignHCenter);
    headingLbl->setText("سامانه کنترل عبور و مرور");
    headingLbl->setGeometry(0, 0, this->width(), 80);
}

void MainWindow::setupRightPanel()
{
    int y = 80;
    int x = this->width()/2 + _windowMargin / 2;
    int width = this->width()/2 - 1.5 * _windowMargin;
    int height = this->height() - y;

    _passwordInput->setEchoMode(QLineEdit::Password);

    _rightPanel->addWidget(_addressInput);
    _rightPanel->addWidget(_usernameInput);
    _rightPanel->addWidget(_passwordInput);
    _rightPanel->addWidget(_connectBtn);

    _rightPanel->setGeometry(QRect(x, y, width, height));
}

void MainWindow::setupLeftPanel()
{
    int y = 80;
    int x = _windowMargin;
    int width = this->width()/2 - 1.5 * _windowMargin;
    int height = this->height() - y;

    _leftPanel->addWidget(_date);
    _leftPanel->addWidget(_time);
    _leftPanel->addWidget(_username);
    _leftPanel->addWidget(_historyBtn);

    _leftPanel->setGeometry(QRect(x, y, width, height));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    this->hide();
    event->accept();
    exit(0);
}

} // end of CPS


