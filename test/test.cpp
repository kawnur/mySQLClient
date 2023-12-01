#include <gtest/gtest.h>
#include <QApplication>
#include <QDir>
#include <QString>

#include "settings.h"
#include "util.h"

#ifdef PROJECT_NAME
    std::string projectName = std::string(PROJECT_NAME);
#else
    std::string projectName = "_TEST_";
#endif


TEST(TestSettings, TestUpdateSettings) {
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

    s1.updateSettings(s2);

    ASSERT_EQ(s1.getSetting("HostName"), s2.getSetting("HostName"));
    ASSERT_EQ(s1.getSetting("Port"), s2.getSetting("Port"));
    ASSERT_EQ(s1.getSetting("DatabaseName"), s2.getSetting("DatabaseName"));
    ASSERT_EQ(s1.getSetting("UserName"), s2.getSetting("UserName"));
    ASSERT_EQ(s1.getSetting("Password"), s2.getSetting("Password"));
}

TEST(TestUtils, TestParseLine) {
    std::filesystem::path tempPath = QDir::tempPath().toStdString();
    auto testPath = tempPath / projectName;

    // create test dir
    QDir testQDir {testPath};

    if(!testQDir.exists()) {
        testQDir.mkdir(QString::fromStdString(testPath.string()));
    }

    // create file
    auto testFilePath = testPath / "test_parseLine";
    QFile testFile(testFilePath);

    ASSERT_FALSE(testFile.exists());

    testFile.open(QIODevice::WriteOnly);
    testFile.write("HostName host1\nPort port1\n");
    testFile.close();

    // parse file
    auto settings = Settings();
    parseFile(settings, testFilePath);

    // remove test file
    testFile.remove();
    ASSERT_FALSE(testFile.exists());

    // test
    ASSERT_EQ(settings.getSetting(QString("HostName")), QString("host1"));
    ASSERT_EQ(settings.getSetting(QString("Port")), QString("port1"));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
