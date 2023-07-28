#ifndef TEST_H
#define TEST_H

#include <QGuiApplication>
#include <QDir>
#include <cassert>
#include <iostream>
#include "settings.h"
#include "util.h"

class Test {
public:
    Test() = default;
    ~Test() = default;

    void runTests();
};

#endif // TEST_H
