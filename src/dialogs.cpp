#include "dialogs.h"

void Dialog::reconnect() {
    Manager* manager = Manager::instance();
    manager->dbReconnect();
}

DBConnectionSettingsDialog::DBConnectionSettingsDialog(QWidget* parent) {
    this->setParent(parent);

    setModal(true);
    setWindowFlag(Qt::Window);

    this->setWindowTitle("DB Connection settings");
    DBConnectionSettings* settings = DBConnectionSettings::instance();

    this->fl = new QFormLayout(this);
    this->setLayout(this->fl);

    QLabel* hostNameLabel = new QLabel("Host name", this);
    QLabel* portNumberLabel = new QLabel("Port number", this);
    QLabel* databaseNameLabel = new QLabel("Database name", this);
    QLabel* userNameLabel = new QLabel("User name", this);
    QLabel* passwordLabel = new QLabel("Passsword", this);

    this->hostNameLineEdit = new QLineEdit(settings->getSetting("HostName"), this);
    this->portLineEdit = new QLineEdit(settings->getSetting("Port"), this);
    this->databaseNameLineEdit = new QLineEdit(settings->getSetting("DatabaseName"), this);
    this->userNameLineEdit = new QLineEdit(settings->getSetting("UserName"), this);
    this->passwordLineEdit = new QLineEdit(settings->getSetting("Password"), this);

    fl->addRow(hostNameLabel, hostNameLineEdit);
    fl->addRow(portNumberLabel, portLineEdit);
    fl->addRow(databaseNameLabel, databaseNameLineEdit);
    fl->addRow(userNameLabel, userNameLineEdit);
    fl->addRow(passwordLabel, passwordLineEdit);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &DBConnectionSettingsDialog::logSettingsAndAccept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    fl->addWidget(buttonBox);
}

void DBConnectionSettingsDialog::logSettingsAndShow() {
    DBConnectionSettings* settings = DBConnectionSettings::instance();
    settings->logState();

    this->show();
}

void DBConnectionSettingsDialog::logSettingsAndAccept() {
    DBConnectionSettings* settings = DBConnectionSettings::instance();
    settings->logState();
    this->logLineEditState();

    if(this->updateSettingsFromLineEdits()) {
        DBConnectionSettingsChangedDialog* dialog = new DBConnectionSettingsChangedDialog(this);
        this->close();
        dialog->show();
    }

    this->accept();
}

void DBConnectionSettingsDialog::logLineEditState() const {
    qInfo() << "hostNameLineEdit: " << this->hostNameLineEdit->text();
    qInfo() << "portLineEdit: " << this->portLineEdit->text();
    qInfo() << "databaseNameLineEdit: " << this->databaseNameLineEdit->text();
    qInfo() << "userNameLineEdit: " << this->userNameLineEdit->text();
}

bool DBConnectionSettingsDialog::updateSettingsFromLineEdits() {
    QString hostName = this->hostNameLineEdit->text();
    QString portNumber = this->portLineEdit->text();
    QString databaseName = this->databaseNameLineEdit->text();
    QString userName = this->userNameLineEdit->text();
    QString password = this->passwordLineEdit->text();

    Settings newSettings = Settings(hostName, portNumber, databaseName, userName, password);

    DBConnectionSettings* settings = DBConnectionSettings::instance();
    bool changed = settings->updateSettings(newSettings);
    return changed;
}

DBTableChoosingDialog::DBTableChoosingDialog(TableChooser* tc) {
    MainWindow* mainWindow = MainWindow::instance();

    setModal(true);
    setParent(mainWindow);
    setWindowFlag(Qt::Window);

    this->tableChooser = tc;
}

void DBTableChoosingDialog::setGeometry() {
    MainWindow* mainWindow = MainWindow::instance();

    QPoint dialogCenter = mapToGlobal(rect().center());
    QPoint mainWindowCenter = mainWindow->mapToGlobal(mainWindow->rect().center());
    QPoint currentPos = pos();
    move(mainWindowCenter - currentPos);
}

void DBTableChoosingDialog::initialize() {
    MainWindow* mainWindow = MainWindow::instance();

    this->setGeometry();

    this->layout = new QVBoxLayout(this);
    this->setLayout(layout);

    this->label = new QLabel(this);
    this->buttonLayout = new QVBoxLayout(this);
    this->buttonBox = new QDialogButtonBox(this);

    layout->addWidget(label);
    layout->addLayout(buttonLayout);
    layout->addWidget(buttonBox);
}

void DBTableChoosingDialog::set() {
    DBPtr* dbPtr = DBPtr::instance();
    bool dbConnectionState = dbPtr->getValue()->isOpen();

    if(dbConnectionState) {
        setWindowTitle("DB table choosing");

        this->label->setText(
                    "Choose one of DB public tables (see DB connection settings):"
                    );

        std::vector<QString>::const_iterator cbegin = tableChooser->tableNames.cbegin();
        std::vector<QString>::const_iterator cend = tableChooser->tableNames.cend();

        for(auto p = cbegin; p != cend; p++) {
            QPushButton* button = new QPushButton(*p, this);
            connect(button, &QPushButton::clicked, this, &DBTableChoosingDialog::getDBTableNameAndClose);
            this->buttonLayout->addWidget(button);
        }

        this->buttonBox->setStandardButtons(QDialogButtonBox::Cancel);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    }

    else {
        this->setWindowTitle("DB is not accessible");

        this->label->setText(
                    "DB is not accessible. Check DB availability and DB connection settings."
                    );

        this->buttonBox->setStandardButtons(QDialogButtonBox::Ok);
        connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::close);
    }
}

void DBTableChoosingDialog::getDBTableNameAndClose() {
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    QString buttonText = buttonSender->text();

    tableChooser->setChosenTableName(buttonText);
    this->close();
}

DBConnectionSettingsChangedDialog::DBConnectionSettingsChangedDialog(QWidget* parent) {
    this->setParent(parent);

    setModal(true);
    setWindowFlag(Qt::Window);

    this->setWindowTitle("DB reconnection");

    QBoxLayout* fl = new QBoxLayout(QBoxLayout::Direction::TopToBottom, this);
    this->setLayout(fl);

    QLabel* reconnectLabel = new QLabel(
                "DB connection settings are changed. \n"
                "Push Reconnect button to connect with new settings.",
                this
                );
    fl->addWidget(reconnectLabel);

    QPushButton* button = new QPushButton("&Reconnect", this);
    connect(button, &QPushButton::clicked, this, &DBConnectionSettingsChangedDialog::closeAndReconnect);
    fl->addWidget(button);
}

void DBConnectionSettingsChangedDialog::closeAndReconnect() {
    this->close();
    this->reconnect();
}

DBReconnectionResultDialog::DBReconnectionResultDialog(bool isOpen, QWidget* parent) {
    this->setParent(parent);

    setModal(true);
    setWindowFlag(Qt::Window);

    this->setWindowTitle("DB reconnection result");

    QBoxLayout* fl = new QBoxLayout(QBoxLayout::Direction::TopToBottom, this);
    this->setLayout(fl);

    QString status = (isOpen) ? QString("IS OPEN") : QString("IS NOT OPEN");
    QLabel* reconnectLabel = new QLabel("DB connection status: Connection " + status, this);
    fl->addWidget(reconnectLabel);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    fl->addWidget(buttonBox);
}
