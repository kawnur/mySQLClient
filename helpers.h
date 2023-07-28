#ifndef HELPERS_H
#define HELPERS_H

#include "util.h"

class DBPtr {
private:
    static DBPtr* _instance;
    QSqlDatabase* value;

    DBPtr();
    ~DBPtr() = default;

public:
    static DBPtr* instance();

    QSqlDatabase* getValue() const;
    void setValue(QSqlDatabase* const);
    bool reOpen();
};

#endif // HELPERS_H
