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
        std::string get_exec_name(std::ifstream &cmakelists);
    }
}
