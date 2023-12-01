#ifndef MYSQLCLIENT_INCLUDE_UTIL_H_
#define MYSQLCLIENT_INCLUDE_UTIL_H_

#include <cstring>
#include <exception>
#include <QCoreApplication>
#include <QFile>
#include <QLibraryInfo>
#include <QLoggingCategory>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QtGlobal>
#include <QVersionNumber>

#include "data.h"
#include "settings.h"

// TODO includes???
// https://google.github.io/styleguide/cppguide.html#Self_contained_Headers
// https://google.github.io/styleguide/cppguide.html#Include_What_You_Use
// https://google.github.io/styleguide/cppguide.html#Forward_Declarations

inline QFile logFilePath {"log"};  // TODO change path at install

class Exception : public std::exception {
private:
    QString message_;
    char* messageChar;

public:
    Exception(const QString& );
    ~Exception();

    const char* what() const noexcept;
};

bool setAndOpenSqlDatabase(QSqlDatabase&);

void logQSqlQueryModelRecords(const QSqlQueryModel*);

void parseQSqlQueryModelRecords(const QSqlQueryModel*, std::vector<QString>&);

std::pair<QString, QString> parseLine(QString&, const QString&);

void parseFile(Settings&, const std::filesystem::path&);

void messageHandler(QtMsgType, const QMessageLogContext&, const QString&);

#endif // MYSQLCLIENT_INCLUDE_UTIL_H_
