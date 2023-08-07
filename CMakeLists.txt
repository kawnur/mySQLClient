cmake_minimum_required(VERSION 3.5)

project(mySQLClient VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Sql)

set(PROJECT_SOURCES
        data.cpp
        data.h
        dialogs.cpp
        dialogs.h
        helpers.cpp
        helpers.h
        main.cpp
        mainwindow.cpp
        mainwindow.h
        manager.cpp
        manager.h
        model.cpp
        model.h
        settings.config
        settings.cpp
        settings.h
        test.cpp
        test.h
        util.cpp
        util.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(mySQLClient
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
     add_executable(mySQLClient
         ${PROJECT_SOURCES}
     )
endif()

target_link_libraries(mySQLClient PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(mySQLClient PRIVATE Qt${QT_VERSION_MAJOR}::Sql)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(mySQLClient)
endif()

file(COPY_FILE settings.config ${CMAKE_BINARY_DIR}/settings.config)
