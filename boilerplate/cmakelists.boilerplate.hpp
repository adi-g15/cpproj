#pragma once

constexpr auto CMAKELISTS_BOILERPLATE =
                            "cmake_minimum_required(VERSION 3.16)\n"
                            "\n"
                            "project(${{CPPROJ_PROJECT_NAME}}\n"
                            "    VERSION 0.0.1\n"
                            "    LANGUAGES CXX\n"
                            "    )\n"
                            "\n"
                            "set(CMAKE_CXX_STANDARD ${{CPPROJ_CXX_STANDARD}})\n"
                            "set(CMAKE_CXX_STANDARD_REQUIRED TRUE)\n"
                            "\n"
                            "file(GLOB SOURCES src/*.cpp)\n"
                            "add_executable(${{CPPROJ_PROJECT_NAME}} ${SOURCES})\n"
                            "\n";
