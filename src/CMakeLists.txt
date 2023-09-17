file(GLOB HEADER_LIST ${PROJECT_SOURCE_DIR}/include/*.h)
file(GLOB SOURCE_LIST ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_library(mySQLClient_lib ${HEADER_LIST} ${SOURCE_LIST})

target_include_directories(mySQLClient_lib PRIVATE ${PROJECT_SOURCE_DIR}/include)
