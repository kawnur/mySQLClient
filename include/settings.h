#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>
#include <map>
#include <QString>
#include <QtDebug>

class Settings {
private:
    QString delimiter = " ";
    std::map<QString, QString> settingsMap {
        {"HostName", ""},
        {"Port", ""},
        {"DatabaseName", ""},
        {"UserName", ""},
        {"Password", ""},
    };

public:
    Settings() = default;
    Settings(
            QString&,
            QString&,
            QString&,
            QString&,
            QString&
            );
    ~Settings() = default;

    QString getDelimiter() const;
    QString getSetting(const QString&) const;
    void setSetting(const std::pair<QString, QString>&);
    bool updateSettings(const Settings&);
    bool find(const QString&) const;
    void logState() const;
};

#endif // SETTINGS_H
