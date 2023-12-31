#include "data.h"

DBConnectionSettings* DBConnectionSettings::_instance = nullptr;

DBConnectionSettings::DBConnectionSettings() {
    this->settings = Settings();
}

void DBConnectionSettings::initialize() {
    // parse settings file
    try {
        parseFile(this->settings, settingsFilePath);
    }
    catch(const Exception& e) {
        qInfo() << e.what();
    }

    // log parsed settings
    this->logState();
}

DBConnectionSettings* DBConnectionSettings::instance() {
    if(_instance == nullptr) {
        _instance = new DBConnectionSettings();
        _instance->initialize();
    }    
    return _instance;
}

QString DBConnectionSettings::getSetting(const QString& key) const {
    return this->settings.getSetting(key);
}

bool DBConnectionSettings::updateSettings(const Settings& newSettings) {
    return this->settings.updateSettings(newSettings);
}

void DBConnectionSettings::logState() const {
    this->settings.logState();
}

TableChooser::TableChooser(Manager* manager_) {
    this->manager = manager_;
    this->model = new QSqlQueryModel;
    this->tableChoosingDialog = new DBTableChoosingDialog(this);
}

TableChooser::~TableChooser() {
    delete this->model;
    delete this->tableChoosingDialog;
}

void TableChooser::initialize() {
    model->setQuery("select table_name from information_schema.tables where table_schema = 'public'");

    logQSqlQueryModelRecords(model);
    parseQSqlQueryModelRecords(model, this->tableNames);

    std::sort(this->tableNames.begin(), this->tableNames.end());

    this->tableChoosingDialog->initialize();
    this->tableChoosingDialog->set();

    QPoint dialogCenterNew = this->tableChoosingDialog->mapToGlobal(this->tableChoosingDialog->rect().center());
    this->tableChoosingDialog->setGeometry();
    this->tableChoosingDialog->show();
}

void TableChooser::setChosenTableName(const QString& s) {
    this->chosenTableName = s;

    // call manager
    emit this->tableNameDefined(this->chosenTableName);
}

QString TableChooser::getChosenTableName() const {
    return this->chosenTableName;
}
