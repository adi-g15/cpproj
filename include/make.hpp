#pragma once

#include <string>
#include "enums.hpp"

namespace make {
    // wanted to use std::32string, but writing the widen is not so simple
    bool generate_project(const std::string &project_name, int cxx_standard, const std::string &project_desc, bool use_git);

    bool write_makefile(const std::string& project_name, int cxx_standard);
    bool write_workflow(const std::string& project_name);
    bool write_readme(const std::string& project_name, int cxx_standard, const std::string &project_desc);
    
    bool build_project(BuildType = BuildType::Debug);
}
