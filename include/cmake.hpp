#pragma once

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string>

// @note - Every function returning bool returns FALSE when FAILS
namespace cmake {
    // wanted to use std::32string, but writing the widen is not so simple
    bool generate_project(const std::string &project_name, int cxx_standard, bool use_git);

    // should be called from PROJECT_ROOT_DIRECTORY
    bool write_cmakelists(const std::string &project_name, int cxx_standard);
    bool write_readme(const std::string& project_name, int cxx_standard);
    bool write_workflow(const std::string& project_name);
}