#include "model.h"

Model::Model(const QString& tableName_) {
    this->tableModel = new QSqlTableModel;
    this->tableName = tableName_;
    this->view = new QTableView;
}

void Model::initialize() {
    this->tableModel->setTable(this->tableName);
    this->tableModel->select();

    MainWindow* mainWindow = MainWindow::instance();
    this->view->setModel(tableModel);

    int index = mainWindow->addTab(this->view, this->tableName);
    this->view->show();
}

Model::~Model() {
    delete this->tableModel;
    delete this->view;
}

void Model::setTableName(const QString& s) {
    this->tableName = s;
}

QTableView* Model::getView() const {
    return this->view;
}

void Model::logState() const {
    qInfo() << "Model: " << this;
    qInfo() << "tableModel: " << this->tableModel;
    qInfo() << "tableName: " << this->tableName;
    qInfo() << "view: " << this->view;
}
