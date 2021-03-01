cmake_minimum_required(VERSION 3.16)

project(tests
    VERSION 0.0.1
    LANGUAGES CXX
    )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

file(GLOB SOURCES src/*.cpp)
add_executable(tests ${SOURCES})
