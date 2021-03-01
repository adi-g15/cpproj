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
file(GLOB CONFIG_FILES all_dep.yml)
include_directories(ext/cxxopts/include)
include_directories(ext/utilpp/includes)
include_directories(ext/rang/include)
include_directories(ext/)
add_executable(cpproj ${SOURCES} ${CONFIG_FILES})

target_include_directories(cpproj PRIVATE include/)
target_include_directories(cpproj PRIVATE ./)

install(TARGETS cpproj DESTINATION bin COMPONENT binaries)
install(FILES ${CONFIG_FILES} DESTINATION etc/cpproj)
set(GLOBAL_CONFIG_LOCATION ${CMAKE_INSTALL_PREFIX}/etc/cpproj)

configure_file(include/configurations.hpp.in configurations.hpp @ONLY)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
