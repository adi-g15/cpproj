#pragma once

#include <string>
#include "enums.hpp"

// @note - Every function returning bool returns FALSE when FAILS
namespace cmake {
    // wanted to use std::32string, but writing the widen is not so simple
    bool generate_project(const std::string &project_name, int cxx_standard, const std::string &project_desc, bool use_git);

    // should be called from PROJECT_ROOT_DIRECTORY
    bool write_cmakelists(const std::string &project_name, int cxx_standard);
    bool write_readme(const std::string& project_name, int cxx_standard, const std::string &project_desc);
    bool write_workflow(const std::string& project_name);

    bool build_project(BuildType = BuildType::Debug);
}
