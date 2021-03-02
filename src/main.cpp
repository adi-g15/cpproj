#include <iostream>
#include <filesystem>
#include <string>
#include <string_view>

#include "cmake.hpp"
#include "make.hpp"
#include "common.hpp"
#include "cpproj.hpp"

#include <rang.hpp>

int main(int argc, const char *argv[]) {
    cxxopts::Options options(
        "cpproj", "A C++ project management tool. Inspired from cargo.");

    cpproj::init(options);

    try {
        auto pData = cpproj::parse(options, argc, argv);

        if (pData.ERR_BIT) {
            std::cout << rang::fg::yellow
                      << "Wrong usage... See the available options: \n\n"
                      << rang::fg::reset;

            cpproj::show_help(options);

            return EXIT_FAILURE;
        } else if(pData.SHOW_HELP) {
            cpproj::show_help(options);
        } else if (pData.EXECUTE) {
            common::execute_exec(pData.EXECUTABLE_NAME);
        } else if (pData.BUILD_IT) {
            common::build_code(pData.BUILD_TYPE);
        } else {
            if (pData.PROJECT_BUILD_MNGR == "cmake") {
                cmake::generate_project(pData.PROJECT_NAME, pData.PROJECT_CXX_STANDARD,
                                        pData.PROJECT_USE_GIT);

            } else if (pData.PROJECT_BUILD_MNGR == "make") {
                std::cout << "Generating a Make Project...\n";

                make::generate_project(pData.PROJECT_NAME, pData.PROJECT_CXX_STANDARD,
                                    pData.PROJECT_USE_GIT);

            }
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (...) { // catch all handler, to be sure of stack unwinding
        std::cerr << "Some Error occured!" << std::endl;
    }
}
