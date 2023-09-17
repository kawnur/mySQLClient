add_executable(test_exe test.cpp)

target_compile_definitions(test_exe PRIVATE PROJECT_NAME="${CMAKE_PROJECT_NAME}")

target_include_directories(test_exe PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(test_exe mySQLClient_lib gtest gtest_main)
