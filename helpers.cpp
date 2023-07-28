#include "helpers.h"

DBPtr* DBPtr::_instance = nullptr;

DBPtr::DBPtr() {
    this->value = nullptr;
}

DBPtr* DBPtr::instance() {
    if(_instance == nullptr) {
        _instance = new DBPtr();
    }
    return _instance;
}

QSqlDatabase* DBPtr::getValue() const {
    return this->value;
}

void DBPtr::setValue(QSqlDatabase* const ptr) {
    this->value = ptr;
}

bool DBPtr::reOpen() {
    this->value->close();
    return setAndOpenSqlDatabase(*(this->value));
}
