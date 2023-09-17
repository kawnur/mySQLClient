#include "util.h"

bool setAndOpenSqlDatabase(QSqlDatabase& db) {
    DBConnectionSettings* connSettings = DBConnectionSettings::instance();

    db.setHostName(connSettings->getSetting("HostName"));
    db.setPort(connSettings->getSetting("Port").toInt());
    db.setDatabaseName(connSettings->getSetting("DatabaseName"));
    db.setUserName(connSettings->getSetting("UserName"));
    db.setPassword(connSettings->getSetting("Password"));

    bool dbConnectionState = db.open();

    if(!dbConnectionState) {
        printError(&db, true);
    }
    return dbConnectionState;
}

void printQSqlQueryModelRecords(const QSqlQueryModel& m) {
    for(int i = 0; i < m.rowCount(); ++i) {
        QSqlRecord r = m.record(i);

        for(int rc = 0; rc < r.count(); rc++) {
            std::string fieldName = r.fieldName(rc).toStdString();
            std::string value = r.value(rc).toString().toStdString();
            std::cout << fieldName << '\t' << value << '\t';
        }
        std::cout << std::endl;
    }
}

void printQSqlQueryModelRecords(const std::vector<std::map<QString, QString>>& v) {
    std::vector<std::map<QString, QString>>::const_iterator cbegin = v.cbegin();
    std::vector<std::map<QString, QString>>::const_iterator cend = v.cend();

    for(auto iter_vec = cbegin; iter_vec != cend; iter_vec++) {
        std::map<QString, QString>::const_iterator cbegin1 = (*iter_vec).cbegin();
        std::map<QString, QString>::const_iterator cend1 = (*iter_vec).cend();

        for(auto iter_map = cbegin1; iter_map != cend1; iter_map++) {
            std::cout << iter_map->first.toStdString() << '\t' << iter_map->second.toStdString() << '\t';
        }
        std::cout << std::endl;
    }
}

void parseQSqlQueryModelRecords(const QSqlQueryModel* m, std::vector<QString>& v) {
    for(int i = 0; i < m->rowCount(); ++i) {
        QSqlRecord r = m->record(i);

        for(int rc = 0; rc < r.count(); rc++) {
            QString value = r.value(rc).toString();
            v.push_back(value);
        }
    }
}

void parseQSqlQueryModelRecords(const QSqlQueryModel* m, std::vector<std::map<QString, QString>>& v) {
    std::map<QString, QString> modelMap;

    for(int i = 0; i < m->rowCount(); ++i) {
        QSqlRecord r = m->record(i);

        for(int rc = 0; rc < r.count(); rc++) {
            QString fieldName = r.fieldName(rc);
            QString value = r.value(rc).toString();
            modelMap[fieldName] = value;
        }
        std::cout << std::endl;
        v.push_back(modelMap);
    }
}

std::pair<QString, QString> parseLine(QString& s, const QString& delimiter) {
    s.replace(QString("\n"), QString(""));
    qsizetype delimiterIndex = s.indexOf(delimiter);

    QString key = s.left(delimiterIndex);
    QString value = s.right(s.length() - delimiterIndex - 1);

    return std::pair<QString, QString> {key, value};
}

void parseFile(Settings& settings, const std::filesystem::path& filePath) {
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    while (!file.atEnd()) {
        QString line = QString(file.readLine());
        QString delimiter = settings.getDelimiter();
        std::pair<QString, QString> pair = parseLine(line, delimiter);

        if(!settings.find(pair.first)) {
            throw Exception(std::string("Unknown key in settings file"));
        }

        settings.setSetting(pair);
    }
}

void printError(const QSqlDatabase* db, bool extended) {
    QSqlError error = db->lastError();

    if(extended) {
        QString applicationDirPath = QCoreApplication::applicationDirPath();
        std::cout << "QCoreApplication::applicationDirPath(): " << applicationDirPath.toStdString() << std::endl;

        QVersionNumber libraryVersion = QLibraryInfo::version();
        std::cout << "libraryVersion: " << libraryVersion.toString().toStdString() << std::endl;
    }
}
