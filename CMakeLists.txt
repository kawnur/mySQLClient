cmake_minimum_required(VERSION 3.14)

project(mySQLClient VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Sql)

link_libraries(Qt${QT_VERSION_MAJOR}::Core)
link_libraries(Qt${QT_VERSION_MAJOR}::Sql)
link_libraries(Qt${QT_VERSION_MAJOR}::Widgets)

add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(test)

enable_testing()
