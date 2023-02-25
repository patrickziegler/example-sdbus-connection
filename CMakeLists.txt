cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

project(sdbusdemo VERSION 0.0.1)

add_subdirectory(client)
add_subdirectory(server)
