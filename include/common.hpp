#pragma once

static constexpr auto TAG_PROJECT_NAME = "${{CPPROJ_PROJECT_NAME}}";
static constexpr auto TAG_CXX_STANDARD = "${{CPPROJ_CXX_STANDARD}}";

#include <string>
#include <fstream>

namespace common {
    bool check_project_existence(const std::string& project_name);
    bool write_main(const std::string& project_name, const std::string& _author = "");
}

/**
 * @brief - Converts standard name in string to a number
 *
 * ie. for `c++17` it returns 17
 *
 * @exception: When the string name isn't valid, ie. starting with c++... or
 * directly an integer eg. "17", then throws an exception
 */
int standard_str_to_num(const std::string &std_name);

bool build_cmake_proj();
bool build_code();

std::string get_exec_name(std::ifstream &cmakelists);
void execute_exec(std::string executable_name = "");
