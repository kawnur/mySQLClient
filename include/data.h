#ifndef MYSQLCLIENT_INCLUDE_DATA_H_
#define MYSQLCLIENT_INCLUDE_DATA_H_

#include <QObject>
#include <QSqlQueryModel>
#include <QString>

#include "dialogs.h"
#include "settings.h"
#include "util.h"

// TODO add namespace ???

class Manager;
class DBTableChoosingDialog;

class DBConnectionSettings {
private:
    static DBConnectionSettings* _instance;
    const std::filesystem::path settingsFilePath = "settings.config";  // TODO change path at install
    Settings settings;

    DBConnectionSettings();
    ~DBConnectionSettings() = default;

    void initialize();

public:
    static DBConnectionSettings* instance();
    QString getSetting(const QString&) const;
    bool updateSettings(const Settings&);
    void logState() const;
};

class TableChooser : public QObject {

    Q_OBJECT

private:
    Manager* manager;
    QSqlQueryModel* model;
    DBTableChoosingDialog* tableChoosingDialog;
    QString chosenTableName;

public:
    std::vector<QString> tableNames;

    TableChooser(Manager*);
    TableChooser(TableChooser&) = default;
    TableChooser& operator=(TableChooser&) = default;
    ~TableChooser();

    void initialize();
    void setChosenTableName(const QString&);
    QString getChosenTableName() const;

signals:
    void tableNameDefined(QString&);
};

#endif // MYSQLCLIENT_INCLUDE_DATA_H_
