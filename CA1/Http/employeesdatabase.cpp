#include "employeesdatabase.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

EmployeesDatabase::EmployeesDatabase(const QString &initialDataPath, QObject *parent) : QObject(parent)
{
    readEmployeesFromJson(initialDataPath);
}

const QVector<Employee>& EmployeesDatabase::getEmployeesVector() const
{
    return employeesVector_;
}

void EmployeesDatabase::readEmployeesFromJson(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open " + path;
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (!doc.isArray()) {
        qDebug() << "Invalid JSON format in " + path;
        return;
    }

    QJsonArray employeesArray = doc.array();
    for (const QJsonValue& employeeValue : employeesArray) {
        if (!employeeValue.isObject()) {
            qDebug() << "Invalid employee data in " + path;
            continue;
        }

        QJsonObject employeeObject = employeeValue.toObject();
        QString rfidTag = employeeObject["rfid"].toString();

        Employee employee(rfidTag);
        employeesVector_.append(employee);
    }
}

bool EmployeesDatabase::handleRfidReceived(const QString &rfid) {
    bool isMatch = false;
    for (const Employee &employee : employeesVector_) {
        if (employee.checkRFIDTagMatched(rfid)) {
            isMatch = true;
            break;
        }
    }

    return isMatch;
}
