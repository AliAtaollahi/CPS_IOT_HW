#include "employee.h"

Employee::Employee() {
    rfidTag_ = nullptr;
}

Employee::Employee(const QString &rfidTag) : rfidTag_(rfidTag) {};

bool Employee::checkRFIDTagMatched(const QString &rfidTag) const{
    return rfidTag_ == rfidTag;
}
