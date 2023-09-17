#include "settings.h"

Settings::Settings(
        QString& hostName, QString& portNumber, QString& databaseName,
        QString& userName, QString& password
        ) {
    this->settingsMap["HostName"] = hostName;
    this->settingsMap["Port"] = portNumber;
    this->settingsMap["DatabaseName"] = databaseName;
    this->settingsMap["UserName"] = userName;
    this->settingsMap["Password"] = password;
}

QString Settings::getDelimiter() const {
    return this->delimiter;
}

QString Settings::getSetting(const QString& key) const {
    return this->settingsMap.at(key);
}

void Settings::setSetting(const std::pair<QString, QString>& pair) {
    if(!this->find(pair.first)) {
        throw("Unknown key at Settings::setValue execution");
    }
    this->settingsMap[pair.first] = pair.second;
}

bool Settings::updateSettings(const Settings& newSettings) {
    bool changed = false;
    std::map<QString, QString>::const_iterator cbegin = this->settingsMap.cbegin();
    std::map<QString, QString>::const_iterator cend = this->settingsMap.cend();

    for(auto p = cbegin; p != cend; p++) {
        std::pair<QString, QString> pair {p->first, newSettings.getSetting(p->first)};
        QString currentValue = this->getSetting(p->first);

        if(currentValue != pair.second) {
            changed = true;
        }
        this->setSetting(pair);
    }
    return changed;
}

bool Settings::find(const QString& key) const {
    if(this->settingsMap.find(key) == this->settingsMap.end()) {
        return false;
    }
    return true;
}

void Settings::printState() const {
    auto printer = [](auto iterator){
        std::cout << "#" << iterator.first.toStdString() << "#" << '\t'
                  << "#" << iterator.second.toStdString() << "#" << std::endl;
    };
    std::for_each(settingsMap.cbegin(), settingsMap.cend(), printer);
}
