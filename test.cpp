#include "test.h"

void test_settings_updateSettings() {
    std::cout << "### test_settings_updateSettings ###" << std::endl;

    QString hn1 = "hn1";
    QString p1 = "p1";
    QString dn1 = "dn1";
    QString un1 = "un1";
    QString pw1 = "pw1";

    QString hn2 = "hn2";
    QString p2 = "p2";
    QString dn2 = "dn2";
    QString un2 = "un2";
    QString pw2 = "pw2";

    Settings s1 = Settings(hn1, p1, dn1, un1, pw1);
    Settings s2 = Settings(hn2, p2, dn2, un2, pw2);

    std::cout << "### before update ###" << std::endl;
    s1.printState();
    s2.printState();

    s1.updateSettings(s2);

    std::cout << "### after update ###" << std::endl;
    s1.printState();
    s2.printState();

    assert(s1.getSetting("HostName") == s2.getSetting("HostName"));
    assert(s1.getSetting("Port") == s2.getSetting("Port"));
    assert(s1.getSetting("DatabaseName") == s2.getSetting("DatabaseName"));
    assert(s1.getSetting("UserName") == s2.getSetting("UserName"));
    assert(s1.getSetting("Password") == s2.getSetting("Password"));
}

void test_printQSqlQueryModelRecords() {
    std::cout << "### test_printQSqlQueryModelRecords ###" << std::endl;

    std::vector<std::map<QString, QString>> v;
    std::map<QString, QString> m1, m2;

    m1[QString("a")] = QString("1");
    m1[QString("b")] = QString("2");

    m2[QString("c")] = QString("3");
    m2[QString("d")] = QString("4");

    v.push_back(m1);
    v.push_back(m2);

    printQSqlQueryModelRecords(v);
}

void test_parseLine() {
    std::cout << "### test_parseLine ###" << std::endl;

    std::filesystem::path tempPath = QDir::tempPath().toStdString();
    auto testPath = tempPath / QApplication::applicationName().toStdString();

    // create test dir
    QDir testQDir = QDir(testPath);

    if(!testQDir.exists()) {
        std::cout << "!testQDir.exists()" << std::endl;
        testQDir.mkdir(QString::fromStdString(testPath.string()));
    }

    // create file
    auto testFilePath = testPath / "test_parseLine";
    QFile testFile(testFilePath);

    if(!testFile.exists()) {
        std::cout << "!testFile.exists()" << std::endl;
        testFile.open(QIODevice::WriteOnly);
        testFile.write("HostName host1\nPort port1\n");
        testFile.close();
    }
    else {
        std::cout << "testFile.exists()" << std::endl;
        throw("testFile exists: " + testFilePath.string());
    }

    // parse file
    auto settings = Settings();
    parseFile(settings, testFilePath);

    // remove test file
    testFile.remove();

    // test
    settings.printState();
    assert(settings.getSetting(QString("HostName")) == QString("host1"));
    assert(settings.getSetting(QString("Port")) == QString("port1"));
}

void Test::runTests() {
    std::cout << "#############################################################" << std::endl;
    std::cout << "### START Test::runTests ###" << std::endl;
    std::cout << "#############################################################" << std::endl;

    test_settings_updateSettings();
    test_printQSqlQueryModelRecords();
    test_parseLine();

    std::cout << "#############################################################" << std::endl;
    std::cout << "### END Test::runTests ###" << std::endl;
    std::cout << "#############################################################" << std::endl;
}
