#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QJsonObject>
#include <QJsonDocument>

class Employee
{
public:
    Employee();
    Employee(const QString &rfidTag);
    bool checkRFIDTagMatched(const QString &rfidTag) const;
private:
    QString rfidTag_;
};

#endif // EMPLOYEE_H
