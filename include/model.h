#ifndef MYSQLCLIENT_INCLUDE_MODEL_H_
#define MYSQLCLIENT_INCLUDE_MODEL_H_

#include <QSqlQueryModel>
#include <QSqlTableModel>

#include "mainwindow.h"

class Model {
private:
    QSqlTableModel* tableModel;
    QString tableName;
    QTableView* view;

public:
    Model(const QString&);
    Model(Model&) = default;
    Model& operator=(Model&) = default;
    ~Model();

    void initialize();
    void setTableName(const QString&);
    QTableView* getView() const;
    void logState() const;
};

#endif // MYSQLCLIENT_INCLUDE_MODEL_H_
