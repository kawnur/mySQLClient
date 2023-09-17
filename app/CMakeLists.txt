add_executable(mySQLClient main.cpp)

target_include_directories(mySQLClient PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(mySQLClient mySQLClient_lib)

file(COPY_FILE ${PROJECT_SOURCE_DIR}/config/settings.config ${CMAKE_CURRENT_BINARY_DIR}/settings.config)
