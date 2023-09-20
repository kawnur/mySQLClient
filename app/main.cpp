#include <QApplication>
#include <QDir>
#include <QString>
#include <QtDebug>
#include <QtGlobal>
#include "data.h"
#include "settings.h"
#include "util.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setApplicationName(QString("mySQLClient"));

    logFilePath.open(QFile::Append | QFile::Text);
    qInstallMessageHandler(messageHandler);

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
