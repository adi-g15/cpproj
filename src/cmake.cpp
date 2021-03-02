#include "cmake.hpp"
#include "common.hpp"
#include "git_connect.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include <util/string.hpp>

#include "boilerplate/cmakelists.boilerplate.hpp"
#include "boilerplate/github_workflow.boilerplate.hpp"
#include "boilerplate/main.boilerplate.hpp"
#include "boilerplate/readme.boilerplate.hpp"

#include "gitignore/gitignore.hpp"

using namespace std::filesystem;

bool cmake::generate_project(const std::string &project_name, int cxx_standard,
                             bool use_git) {
    bool all_successful = true;

    std::cout << "Generating a CMake Project...\n";

    common::check_project_existence(project_name);

    create_directory(project_name);
    current_path(project_name); // for the rest of project we will cd into the
                                // project directory

    create_directories("src");
    create_directories("include");

    all_successful = common::write_main(project_name) && true;
    all_successful =
        cmake::write_cmakelists(project_name, cxx_standard) && true;
    all_successful = cmake::write_readme(project_name, cxx_standard) && true;

    if (use_git) {
        all_successful = cmake::write_workflow(project_name) && true;
        gitignore::create_gitignore({
            GITIGNORE_FLAGS::CPP_GENERAL,
            GITIGNORE_FLAGS::CMAKE,
            GITIGNORE_FLAGS::VS_CODE,
        });

        git_connect::init_git_repo();
    }

    current_path("../"); // return to the original directory

    return all_successful;
}

bool cmake::write_cmakelists(const std::string &project_name,
                             int cxx_standard) {
    std::ofstream CMakeLists("CMakeLists.txt");
    std::string CMAKELISTS_BOILERPLATE_(CMAKELISTS_BOILERPLATE);
    util::replace_all(CMAKELISTS_BOILERPLATE_, TAG_PROJECT_NAME, project_name);
    util::replace_all(CMAKELISTS_BOILERPLATE_, TAG_CXX_STANDARD,
                      std::to_string(cxx_standard));
    CMakeLists << CMAKELISTS_BOILERPLATE_;
    CMakeLists.close();
}

// should be called from PROJECT_ROOT_DIRECTORY
bool cmake::write_workflow(const std::string &project_name) {
    create_directories(".github/workflows");
    std::string CMAKE_WORKFLOW_BOILERPLATE_(CMAKE_WORKFLOW_BOILERPLATE);

    std::ofstream CMakeWorkflow(".github/workflows/build.yml");

    util::replace_all(CMAKE_WORKFLOW_BOILERPLATE_, TAG_PROJECT_NAME,
                      project_name);

    CMakeWorkflow << CMAKE_WORKFLOW_BOILERPLATE_;

    CMakeWorkflow.close();
}

bool cmake::write_readme(const std::string &project_name, int cxx_standard) {
    std::ofstream readme("README.md");

    if (!readme)
        return false;

    std::string README_BOILERPLATE_ = README_CMAKE_BOILERPLATE;
    util::replace_all(README_BOILERPLATE_, TAG_PROJECT_NAME, project_name);
    util::replace_all(README_BOILERPLATE_, TAG_CXX_STANDARD,
                      std::to_string(cxx_standard));

    readme << README_BOILERPLATE_;
    readme.close();

    return true;
}
