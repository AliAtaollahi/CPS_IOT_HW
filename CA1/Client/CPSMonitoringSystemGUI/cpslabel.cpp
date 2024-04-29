#include "cpslabel.h"

namespace CPS {

Label::Label(const QString &text, QWidget *parent)
    : QLabel{parent}
{
    QFont fontInput;
    fontInput.setPixelSize(20);
    fontInput.setBold(false);

    this->setMinimumHeight(70);
    this->setMaximumHeight(70);
    this->setFont(fontInput);
    this->setMargin(10);
    this->setText(text);
}

} // end of CPS
