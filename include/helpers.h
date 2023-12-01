#ifndef MYSQLCLIENT_INCLUDE_HELPERS_H_
#define MYSQLCLIENT_INCLUDE_HELPERS_H_

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

#endif // MYSQLCLIENT_INCLUDE_HELPERS_H_
