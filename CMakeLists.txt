cmake_minimum_required(VERSION 3.16)

project(CPProj
    VERSION 0.0.1
    LANGUAGES CXX
    )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

if(NOT IS_DIRECTORY "ext/cxxopts/include")
    message(FATAL_ERROR "Dependencies not cloned. "
        "\nClone using `git submodule update --init --depth=1`"
    )
endif()

file(GLOB SOURCES src/*.cpp)
include_directories(ext/cxxopts/include)

add_executable(cpproj ${SOURCES})
