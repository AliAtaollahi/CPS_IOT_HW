#ifndef CPSBUTTON_H
#define CPSBUTTON_H

#include <QWidget>
#include <QPushButton>

namespace CPS {

class Button : public QPushButton
{
    Q_OBJECT
public:
    explicit Button(const QString &text, QWidget *parent = nullptr);

signals:
};

} // end of CPS

#endif // CPSBUTTON_H
