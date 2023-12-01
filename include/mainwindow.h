#ifndef MYSQLCLIENT_INCLUDE_MAINWINDOW_H_
#define MYSQLCLIENT_INCLUDE_MAINWINDOW_H_

#include <QApplication>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QTableView>
#include <QVBoxLayout>

#include "dialogs.h"
#include "manager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    static MainWindow* _instance;
    static int tabIndex;

    MainWindow(QWidget* parent = nullptr);
    ~MainWindow() = default;

    void createConnection();

public:
    static MainWindow* instance();
    QTabWidget* tabWidget;

    int addTab(QTableView*, const QString&);
    void createMenu();

public slots:
    void closeTab(int);
};

#endif // MYSQLCLIENT_INCLUDE_MAINWINDOW_H_
