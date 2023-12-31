#ifndef MYSQLCLIENT_INCLUDE_DIALOGS_H_
#define MYSQLCLIENT_INCLUDE_DIALOGS_H_

#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "data.h"
#include "manager.h"

class MainWindow;
class TableChooser;

class Dialog : public QDialog {

    Q_OBJECT

public slots:
    void reconnect();
};

class DBConnectionSettingsDialog : public Dialog {

    Q_OBJECT

private:
    QFormLayout* fl;
    QDialogButtonBox* buttonBox;
    QLineEdit* hostNameLineEdit;
    QLineEdit* portLineEdit;
    QLineEdit* databaseNameLineEdit;
    QLineEdit* userNameLineEdit;
    QLineEdit* passwordLineEdit;

public:
    DBConnectionSettingsDialog(QWidget*);
    ~DBConnectionSettingsDialog() = default;

    void logSettingsAndAccept();
    void logSettingsAndShow();
    void logLineEditState() const;
    bool updateSettingsFromLineEdits();
};

class DBTableChoosingDialog : public Dialog {

    Q_OBJECT

private:
    TableChooser* tableChooser;
    QVBoxLayout* layout;
    QLabel* label;
    std::vector<QPushButton*> buttons;
    QVBoxLayout* buttonLayout;
    QDialogButtonBox* buttonBox;

public:
    DBTableChoosingDialog(TableChooser*);
    ~DBTableChoosingDialog() = default;

    void initialize();
    void set();
    void setGeometry();

public slots:
    void getDBTableNameAndClose();
};

class DBConnectionSettingsChangedDialog : public Dialog {

    Q_OBJECT

public:
    DBConnectionSettingsChangedDialog(QWidget*);
    ~DBConnectionSettingsChangedDialog() = default;

public slots:
    void closeAndReconnect();
};

class DBReconnectionResultDialog : public Dialog {

    Q_OBJECT

public:
    DBReconnectionResultDialog(bool, QWidget*);
    ~DBReconnectionResultDialog() = default;
};

#endif // MYSQLCLIENT_INCLUDE_DIALOGS_H_
