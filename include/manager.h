#ifndef MYSQLCLIENT_INCLUDE_MANAGER_H_
#define MYSQLCLIENT_INCLUDE_MANAGER_H_

#include <QObject>
#include <QSqlQueryModel>

#include "data.h"
#include "helpers.h"
#include "model.h"

class Model;
class TableChooser;

class Manager : public QObject {

    Q_OBJECT

private:
    static Manager* _instance;
    TableChooser* tableChooser;
    QSqlQueryModel* queryModel;
    std::vector<std::unique_ptr<Model>> models;
    std::vector<Model*> v1;

    Manager();
    ~Manager() = default;

    void appendModel(const QString&);

public:
    static Manager* instance();
    void initializeTableChooser();
    void eraseModelByTableView(QTableView*);
    void logModels() const;

public slots:
    void defineTableName(const QString&);
    void addModel();
    void dbReconnect();
};

#endif // MYSQLCLIENT_INCLUDE_MANAGER_H_
