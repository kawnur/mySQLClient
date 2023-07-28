#include <QApplication>
#include "data.h"
#include "test.h"

int main(int argc, char *argv[]) {
    // run app
    QApplication a(argc, argv);
    a.setApplicationName(QString("mySQLClient"));

    // run tests
    Test test;
    test.runTests();

    DBConnectionSettings* connSettings = DBConnectionSettings::instance();
    QSqlDatabase dataBase = QSqlDatabase::addDatabase("QPSQL");
    auto dbConnectionState = setAndOpenSqlDatabase(dataBase);

    DBPtr* dbPtr = DBPtr::instance();
    dbPtr->setValue(&dataBase);

    MainWindow* mainWindow = MainWindow::instance();

    mainWindow->createMenu();
    mainWindow->show();

    Manager* manager = Manager::instance();
    manager->initializeTableChooser();
    return a.exec();
}
