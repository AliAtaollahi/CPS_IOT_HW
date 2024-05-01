#include "employeesdatabase.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

EmployeesDatabase::EmployeesDatabase(const QString &initialDataPath, QObject *parent) : QObject(parent)
{
    loadEmployeesFromJson(initialDataPath);
}

const QVector<Employee>& EmployeesDatabase::getEmployeesVector() const
{
    return employeesVector_;
}

void EmployeesDatabase::loadEmployeesFromJson(const QString &path)
{
    QByteArray jsonData = readJsonFile(path);
    if (!jsonData.isEmpty()) {
        parseEmployeesJson(jsonData);
    }
}

QByteArray EmployeesDatabase::readJsonFile(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open " + path;
        return QByteArray();
    }

    QByteArray jsonData = file.readAll();
    file.close();

    return jsonData;
}

void EmployeesDatabase::parseEmployeesJson(const QByteArray &jsonData)
{
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (!doc.isArray()) {
        qDebug() << "Invalid JSON format";
        return;
    }

    QJsonArray employeesArray = doc.array();
    for (const QJsonValue& employeeValue : employeesArray) {
        if (!employeeValue.isObject()) {
            qDebug() << "Invalid employee data";
            continue;
        }

        QJsonObject employeeObject = employeeValue.toObject();
        QString rfidTag = employeeObject["rfid"].toString();

        Employee employee(rfidTag);
        employeesVector_.append(employee);
    }
}

bool EmployeesDatabase::checkRFIDMatch(const QString &rfid)
{
    bool isMatch = false;
    for (const Employee &employee : employeesVector_) {
        if (employee.checkRFIDTagMatched(rfid)) {
            isMatch = true;
            break;
        }
    }

    return isMatch;
}
