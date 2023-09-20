#include "manager.h"

Manager* Manager::_instance = nullptr;

Manager* Manager::instance() {
    if(_instance == nullptr) {
        _instance = new Manager();
    }
    return _instance;
}

Manager::Manager() {
    this->tableChooser = new TableChooser(this);
    this->queryModel = new QSqlQueryModel(this);
}

void Manager::initializeTableChooser() {
    connect(this->tableChooser, &TableChooser::tableNameDefined, this, &Manager::defineTableName);
    this->tableChooser->initialize();
}

void Manager::eraseModelByTableView(QTableView* tableView) {
    auto compareView = [&](std::unique_ptr<Model>& m){ return m.get()->getView() == tableView; };
    auto it = std::find_if(this->models.begin(), this->models.end(), compareView);

    this->models.erase(it);
    this->logModels();
}

void Manager::appendModel(const QString& tableName) {
    auto model = std::make_unique<Model>(tableChooser->getChosenTableName());
    model->initialize();
    this->models.push_back(std::move(model));
    this->logModels();
}

void Manager::logModels() const {
    auto logger = [&](const std::unique_ptr<Model>& model){ model->logState(); };
    qInfo() << "Manager.models.size(): " << this->models.size();
    std::for_each(this->models.begin(), this->models.end(), logger);
}

void Manager::defineTableName(const QString& tableName) {
    this->appendModel(tableName);
}

void Manager::addModel() {
    TableChooser* newTableChooser = new TableChooser(this);
    TableChooser* oldTableChooser = this->tableChooser;
    this->tableChooser = newTableChooser;
    this->initializeTableChooser();
    delete oldTableChooser;
}

void Manager::dbReconnect() {
    DBPtr* dbPtr = DBPtr::instance();
    bool dbConnectionReOpen = dbPtr->reOpen();
    DBReconnectionResultDialog* dialog = new DBReconnectionResultDialog(dbConnectionReOpen, qobject_cast<QWidget*>(this));
    dialog->show();
}
