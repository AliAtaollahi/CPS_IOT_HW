#ifndef CPSTEXTFIELD_H
#define CPSTEXTFIELD_H

#include <QWidget>
#include <QLineEdit>

namespace CPS {

class TextField : public QLineEdit
{
    Q_OBJECT
public:
    explicit TextField(const QString &placeholderText, QWidget *parent = nullptr);

signals:
};

} // end of CPS

#endif // CPSTEXTFIELD_H
