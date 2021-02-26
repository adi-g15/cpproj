project(CPProj
    VERSION 0.0.1
    LANG CXX
    )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

file(GLOB SOURCES src/*.cpp)
add_executable(cpproj ${SOURCES})
