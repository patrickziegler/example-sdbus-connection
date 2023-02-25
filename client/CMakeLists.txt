find_package(sdbus-c++ REQUIRED)

set(TARGET_NAME client)

add_executable(${TARGET_NAME})

target_sources(${TARGET_NAME} PRIVATE
    main.cpp)

target_link_libraries(${TARGET_NAME} PRIVATE
    SDBusCpp::sdbus-c++)
