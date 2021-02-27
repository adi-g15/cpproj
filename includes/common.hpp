#pragma once

static constexpr auto TAG_PROJECT_NAME = "${{CPPROJ_PROJECT_NAME}}";
static constexpr auto TAG_CXX_STANDARD = "${{CPPROJ_CXX_STANDARD}}";

#include <algorithm>
#include <filesystem>
#include <string>
#include <string_view>

#include <rang.hpp>
#include <util/file.hpp>
#include <util/string.hpp>

#include "make.hpp"

namespace fs = std::filesystem;

/**
 * @brief - Converts standard name in string to a number
 *
 * ie. for `c++17` it returns 17
 *
 * @exception: When the string name isn't valid, ie. starting with c++... or
 * directly an integer eg. "17", then throws an exception
 */
int standard_str_to_num(const std::string &std_name) {
    std::string_view standard_str(std_name);
    if (util::starts_with(std_name, "c++")) {
        standard_str.remove_prefix(
            std::size("c++")); // WILL NOT BE UNDEFINED BEHAVIOUS, since string
                               // already atleast of 3 length
    }

    // by now, the string MUST ONLY contain an integer
    return std::stoi(standard_str.data());
}

bool build_cmake_proj() {
    if (exists("CMakeLists.txt")) {
        create_directory("build");

        std::filesystem::current_path("build"); // cd to build
    }

    if (exists("../CMakeLists.txt")) {
        std::system("cmake .. && cmake --build .");

        return true;
    } else
        return false;
}

// returns whether the build was `attempted`
bool build_code() {
    bool is_cmake_proj;

    is_cmake_proj = fs::exists("CMakeLists.txt");

    if (is_cmake_proj)
        return build_cmake_proj();
    else if (fs::exists("Makefile"))
        return build_make_proj();
    else {
        std::cerr << "[Error] Not in a project, or build system/generator not "
                     "supported\n";

        return false;
    }
}

std::string get_exec_name(std::ifstream &cmakelists) {
    if (!cmakelists)
        return "";

    std::string content = util::read_file(cmakelists);
    auto iter = std::next(content.begin(), content.find("add_executable"));

    iter = std::find_if(iter, content.end(),
                        [](char ch) { return !std::isspace(ch) && ch != '('; });

    if (iter == content.end())
        return "";

    return std::string(iter, std::find_if(iter, content.end(), [](char ch) {
                           return std::isspace(ch);
                       }));
}

void execute_exec(const std::string &executable_name = "") {
    if (!build_code())
        return;

    std::string executable_path;
    std::ifstream cmakelists;

    if (fs::exists("CMakeLists.txt")) {
        cmakelists.open("CMakeLists.txt");

        if (cmakelists) {
            get_exec_name(cmakelists);
        } else if (!executable_name.empty()) {
            executable_path = "build/" + executable_name;
            if (!fs::exists(executable_path))
                executable_path = "build/Debug/" + executable_path + ".exe";

            std::system(executable_path.data());
        }
    } else if (fs::exists("CMakeCache.txt")) {
        cmakelists.open("../CMakeLists.txt");

        if (cmakelists) {
            get_exec_name(cmakelists);
        } else if (!executable_name.empty()) {
            executable_path = executable_name;
            if (!fs::exists(executable_path))
                executable_path = "Debug/" + executable_path + ".exe";

            std::system(executable_path.data());
        }
    }

    if (executable_path.empty()) {
        std::cerr << rang::fg::red
                  << "[Error] Couldn't know the executable name\n"
                  << rang::fg::reset
                  << "[Tip] It occurs since an add_executable was not found in "
                     "your root CMakeLists.txt file\n You may pass it manually "
                     "using ---exec";

        return;
    }
}
