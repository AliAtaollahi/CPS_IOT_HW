#ifndef CPSLABEL_H
#define CPSLABEL_H

#include <QLabel>
namespace CPS {

class Label : public QLabel
{
    Q_OBJECT
public:
    explicit Label(const QString &text, QWidget *parent = nullptr);

signals:
};

} // end of CPS


#endif // CPSLABEL_H
