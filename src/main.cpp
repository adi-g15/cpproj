#include <filesystem>
#include <set>
#include <string>
#include <string_view>

#include "options.hpp"
#include "cmake.hpp"
#include "make.hpp"

int main(int argc, const char *argv[]) {
    std::set<std::string> used_args;

    std::string PROJECT_NAME;
    int PROJECT_CXX_STANDARD;
    std::string PROJECT_BUILD_MNGR;
    bool PROJECT_USE_GIT;

    cxxopts::Options options(
        "cpproj", "A C++ project management tool. Inspired from cargo.");
    // options.allow_unrecog(nised_options();

    set_options(options);   // set supported operations

    try {
        const auto &result = options.parse(argc, argv);
        const auto &unmatched_args = result.unmatched();

        if (argc == 1 || result.count("help") > 0) {
            show_help(options);

            return 0;
        } else if(result.count("build") > 0) {
            build_code();
        } else if(result.count("run") > 0) {
            execute_exec(result.count("exec") > 0 ? result["exec"].as<std::string>(): "");
        }

        for (const auto &arg : result.arguments()) {
            used_args.insert(arg.value());
        }

        if (result.count("name") > 0)
            PROJECT_NAME = result["name"].as<std::string>();

        if (PROJECT_NAME.empty() && result.count("build") == 0 && result.count("run") == 0) {
            std::cout << rang::fg::yellow << "Wrong usage... See the available options: \n\n" << rang::fg::reset;

            show_help(options);

            return EXIT_FAILURE;
        }

        for (const auto &arg : result.unmatched()) {
            if (used_args.find(arg) ==
                used_args
                    .end()) { // first unmatched argument is considered the name
                PROJECT_NAME = arg;
                break;
            }
        }

        if (PROJECT_NAME.empty())
            throw std::logic_error("PROJECT_NAME was empty");
        PROJECT_CXX_STANDARD =
            result.count("std") > 0
                ? standard_str_to_num(result["std"].as<std::string>())
                : 17;
        PROJECT_BUILD_MNGR = result.count("build_sys") > 0
                                 ? result["build_sys"].as<std::string>()
                                 : "cmake";
        PROJECT_USE_GIT =
            result.count("no-git") > 0 ? !result["no-git"].as<bool>() : true;

        switch (PROJECT_CXX_STANDARD) {
        case 98:
        case 11:
        case 14:
        case 17:
        case 20:
            break;
        default:
            std::cout << "Warning: Invalid C++ standard passed: "
                      << PROJECT_CXX_STANDARD << "Defaulting to C++17\n";
            PROJECT_CXX_STANDARD = 17;
            break;
        }

        if (PROJECT_BUILD_MNGR == "cmake") {
            std::cout << "Generating a CMake Project...\n";

            generate_cmake_project(PROJECT_NAME, PROJECT_CXX_STANDARD,
                                   PROJECT_USE_GIT);

        } else if (PROJECT_BUILD_MNGR == "make") {
            std::cout << "Generating a Make Project...\n";

            generate_make_project(PROJECT_NAME, PROJECT_CXX_STANDARD,
                                  PROJECT_USE_GIT);

        } else {
            std::cout << "[Warning] " << PROJECT_BUILD_MNGR
                      << " not supported\n";
            std::cout << "Generating a CMake Project...\n";

            generate_cmake_project(PROJECT_NAME, PROJECT_CXX_STANDARD,
                                   PROJECT_USE_GIT);
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (...) { // catch all handler, to be sure of stack unwinding
        std::cerr << "Some Error occured!" << std::endl;
    }
}
