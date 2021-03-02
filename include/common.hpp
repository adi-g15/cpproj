#pragma once

static constexpr auto TAG_PROJECT_NAME = "${{CPPROJ_PROJECT_NAME}}";
static constexpr auto TAG_CXX_STANDARD = "${{CPPROJ_CXX_STANDARD}}";
static constexpr auto TAG_PROJECT_DESC = "${{CPPROJ_PROJECT_DESC}}";
static constexpr auto EXTERNAL_DEPENDENCY_DIR =
    "ext"; // the directory which holds our dependencies (when using submodules)

#include <fstream>
#include <string>

#include "enums.hpp"

#define CPPROJ_NO_DISCARD [[nodiscard]]

namespace common {
CPPROJ_NO_DISCARD
bool check_project_existence(const std::string &project_name);
bool write_main(const std::string &project_name,
                const std::string &_author = "");

bool build_code(BuildType = BuildType::Debug);
void execute_exec(std::string executable_name = "");

namespace _impl {
std::string get_exec_name(std::ifstream &cmakelists);
}
} // namespace common
