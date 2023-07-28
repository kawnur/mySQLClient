#ifndef UTIL_H
#define UTIL_H

#include <exception>
#include <QCoreApplication>
#include <QFile>
#include <QLibraryInfo>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QVersionNumber>
#include "data.h"
#include "settings.h"


class Exception : public std::exception {
private:
    std::string message_;
public:
    Exception(const std::string& message) {
        message_ = "EXCEPTION: " + message;
    };
    const char* what() const noexcept {
        return message_.c_str();
    };
};

bool setAndOpenSqlDatabase(QSqlDatabase&);

void printQSqlQueryModelRecords(const QSqlQueryModel&);
void printQSqlQueryModelRecords(const std::vector<std::map<QString, QString>>&);

void parseQSqlQueryModelRecords(const QSqlQueryModel*, std::vector<QString>&);
void parseQSqlQueryModelRecords(const QSqlQueryModel*, std::vector<std::map<QString, QString>>&);

std::pair<QString, QString> parseLine(QString&, const QString&);

void parseFile(Settings&, const std::filesystem::path&);

void printError(const QSqlDatabase*, bool);

#endif // UTIL_H
