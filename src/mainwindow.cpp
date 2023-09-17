#include "mainwindow.h"

MainWindow* MainWindow::_instance = nullptr;

MainWindow* MainWindow::instance() {
    if(_instance == nullptr) {
        _instance = new MainWindow();        
    }
    return _instance;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    this->setGeometry(0, 0, 800, 600);
    this->setWindowTitle(QString("MainWindow"));

    this->menuBar()->setGeometry(0, 0, 800, 24);

    this->tabWidget = new QTabWidget(this);
    this->tabWidget->setTabsClosable(true);
    this->tabWidget->setMovable(true);
    connect(this->tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);
    this->setCentralWidget(tabWidget);
}

int MainWindow::addTab(QTableView* view, const QString& tableName) {
    int index = this->tabWidget->addTab(view, tableName);
    this->tabWidget->setCurrentIndex(index);
    return index;
}

void MainWindow::closeTab(int index) {
    QWidget* widget = this->tabWidget->widget(index);
    QTableView* tableView = qobject_cast<QTableView*>(widget);

    Manager* manager = Manager::instance();
    manager->eraseModelByTableView(tableView);
}

void MainWindow::createMenu() {
    Manager* manager = Manager::instance();

    DBConnectionSettingsDialog* dialog = new DBConnectionSettingsDialog(this);

    QMenu* fileMenu = menuBar()->addMenu("File");
    QAction* exitAct = new QAction("Exit", this);
    fileMenu->addAction(exitAct);
    connect(exitAct, &QAction::triggered, this, &QCoreApplication::quit);

    QMenu* modelMenu = menuBar()->addMenu("Model");
    QAction* addModelAct = new QAction("Add model", this);
    modelMenu->addAction(addModelAct);
    connect(addModelAct, &QAction::triggered, manager, &Manager::addModel);

    QMenu* connectionMenu = menuBar()->addMenu("Connection");
    QAction* reconnectAct = new QAction("Reconnect", this);
    connectionMenu->addAction(reconnectAct);
    connect(reconnectAct, &QAction::triggered, manager, &Manager::dbReconnect);

    QMenu* settingsMenu = menuBar()->addMenu("Settings");
    QAction* settingsAct = new QAction("DB Connection", this);
    settingsMenu->addAction(settingsAct);
    connect(settingsAct, &QAction::triggered, dialog, &DBConnectionSettingsDialog::printSettingsAndShow);
}
