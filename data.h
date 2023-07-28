#ifndef DATA_H
#define DATA_H

#include <QObject>
#include <QSqlQueryModel>
#include <QString>
#include "dialogs.h"
#include "settings.h"
#include "util.h"

class Manager;
class DBTableChoosingDialog;

class DBConnectionSettings {
private:
    static DBConnectionSettings* _instance;
    const std::filesystem::path settingsFilePath = "settings.config";
    Settings settings;

    DBConnectionSettings();
    ~DBConnectionSettings() = default;

    void initialize();

public:
    static DBConnectionSettings* instance();
    QString getSetting(const QString&) const;
    bool updateSettings(const Settings&);
    void printState() const;
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

#endif // DATA_H
