#include "util.h"

// TODO https://google.github.io/styleguide/cppguide.html#Internal_Linkage

Exception::Exception(const QString& message) {
    message_ = QString("EXCEPTION: ") + message;
    int size = message_.size();
    messageChar = new char[size];
    std::string messageToStdString = message_.toStdString();
    const char* data = messageToStdString.c_str();
    strncpy(messageChar, data, message_.size());
};

Exception::~Exception() {
    delete[] messageChar;
};

const char* Exception::what() const noexcept {
    return messageChar;
};

bool setAndOpenSqlDatabase(QSqlDatabase& db) {
    DBConnectionSettings* connectionSettings = DBConnectionSettings::instance();

    db.setHostName(connectionSettings->getSetting("HostName"));
    db.setPort(connectionSettings->getSetting("Port").toInt());
    db.setDatabaseName(connectionSettings->getSetting("DatabaseName"));
    db.setUserName(connectionSettings->getSetting("UserName"));
    db.setPassword(connectionSettings->getSetting("Password"));

    return db.open();
}

void logQSqlQueryModelRecords(const QSqlQueryModel* model) {
    for(int i = 0; i < model->rowCount(); ++i) {
        QSqlRecord record = model->record(i);

        for(int rc = 0; rc < record.count(); rc++) {
            qInfo() << record.fieldName(rc) << '\t' << record.value(rc).toString();
        }
    }
}

void parseQSqlQueryModelRecords(const QSqlQueryModel* model, std::vector<QString>& vector_) {
    for(int i = 0; i < model->rowCount(); ++i) {
        QSqlRecord record = model->record(i);

        for(int rc = 0; rc < record.count(); rc++) {
            QString value = record.value(rc).toString();
            vector_.push_back(value);
        }
    }
}

std::pair<QString, QString> parseLine(QString& string_, const QString& delimiter) {
    string_.replace(QString("\n"), QString(""));
    qsizetype delimiterIndex = string_.indexOf(delimiter);

    QString key = string_.left(delimiterIndex);
    QString value = string_.right(string_.length() - delimiterIndex - 1);

    return std::pair<QString, QString> {key, value};
}

void parseFile(Settings& settings, const std::filesystem::path& filePath) {
    QFile file(filePath);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw Exception("Settings file was not found");
    }

    while(!file.atEnd()) {
        QString line = QString(file.readLine());
        QString delimiter = settings.getDelimiter();
        std::pair<QString, QString> pair = parseLine(line, delimiter);

        if(!settings.find(pair.first)) {
            throw Exception("Unknown key in settings file: " + pair.first);
        }

        settings.setSetting(pair);
    }
}

void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& message) {
    QTextStream out {&logFilePath};

    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");

    switch(type)
    {
        case QtInfoMsg:     out << "[INFO]     "; break;
        case QtDebugMsg:    out << "[DEBUG]    "; break;
        case QtWarningMsg:  out << "[WARNING]  "; break;
        case QtCriticalMsg: out << "[CRITICAL] "; break;
        case QtFatalMsg:    out << "[FATAL]    "; break;
    }

    out << context.category << ": " << message << "\n";
    out.flush();
}
