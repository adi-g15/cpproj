cmake_minimum_required(VERSION 3.16)

project(CPProj
    VERSION 0.0.1
    LANGUAGES CXX
    )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
# set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)

# if(NOT IS_DIRECTORY "ext/cxxopts/include")
#     message(FATAL_ERROR "Dependencies not cloned. "
#         "\nClone using `git submodule update --init --depth=1`"
#     )
# endif()

file(GLOB SOURCES src/*.cpp)
include_directories(ext/cxxopts/include)
include_directories(ext/utilpp/includes)
add_executable(cpproj ${SOURCES})

target_include_directories(cpproj PRIVATE includes/)
target_include_directories(cpproj PRIVATE ./)

add_compile_options(-g)

install(TARGETS cpproj DESTINATION bin)
