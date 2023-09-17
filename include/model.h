#ifndef MODEL_H
#define MODEL_H

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
    void printState() const;
};

#endif // MODEL_H
