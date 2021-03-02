#pragma once

static constexpr auto TAG_PROJECT_NAME = "${{CPPROJ_PROJECT_NAME}}";
static constexpr auto TAG_CXX_STANDARD = "${{CPPROJ_CXX_STANDARD}}";

#include <string>
#include <fstream>

#include "enums.hpp"

#define NO_DISCARD [[nodiscard]]

namespace common {
    NO_DISCARD bool check_project_existence(const std::string& project_name);
    bool write_main(const std::string& project_name, const std::string& _author = "");

    bool build_code(BuildType = BuildType::Debug);
    void execute_exec(std::string executable_name = "");

    namespace _impl {
        /**
         * @brief - Converts standard name in string to a number
         *
         * ie. for `c++17` it returns 17
         *
         * @exception: When the string name isn't valid, ie. starting with c++... or
         * directly an integer eg. "17", then throws an exception
         */
        int standard_str_to_num(const std::string &std_name);
        std::string get_exec_name(std::ifstream &cmakelists);
    }
}
