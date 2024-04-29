#include "cpstextfield.h"

namespace CPS {

TextField::TextField(const QString &placeholderText, QWidget *parent)
    : QLineEdit{parent}
{
    QFont fontInput;
    fontInput.setPixelSize(20);
    fontInput.setBold(false);

    this->setMinimumHeight(70);
    this->setMaximumHeight(70);
    this->setFont(fontInput);
    this->setTextMargins(10, 0, 10, 0);
    this->setPlaceholderText(placeholderText);
    this->setStyleSheet("QLineEdit {border-top: 0px; border-left: 0px; \
                         border-right: 0px; border-bottom: 2px solid #E0E0E0; \
                         color: #E0E0E0; background-color: #202020;  } \
                         QLineEdit:hover {background-color: #303030;} \
                         QLineEdit:focus {border-bottom: 2px solid #4CAF50;}");
}

} // end of CPS
