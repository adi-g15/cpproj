#include "make.hpp"

#include <iostream>
#include <filesystem>
#include <string>

#include <util/string.hpp>
#include "common.hpp"
#include "git_connect.hpp"

#include "boilerplate/github_workflow.boilerplate.hpp"
#include "boilerplate/makefile.boilerplate.hpp"
#include "boilerplate/readme.boilerplate.hpp"

#include "gitignore/gitignore.hpp"

bool make::generate_project(const std::string &project_name, int cxx_standard,
                        const std::string &project_desc, bool use_git) {
    using namespace std::filesystem;

    bool all_successful = true;

    std::cout << "Generating a Make Project...\n";

    if( common::check_project_existence(project_name) ) return false;

    create_directory(project_name);
    current_path(project_name); // for the rest of project we will cd into the
                                // project directory

    create_directory("src");
    create_directory("include");

    all_successful = common::write_main(project_name, project_desc) && true;
    all_successful =
        make::write_makefile(project_name, cxx_standard) && true;
    all_successful = make::write_readme(project_name, cxx_standard, project_desc) && true;

    if (use_git) {
        all_successful = make::write_workflow(project_name) && true;
        gitignore::create_gitignore({
            GITIGNORE_FLAGS::CPP_GENERAL
        });

        git_connect::init_git_repo();
    }

    current_path("../"); // return to the original directory

    return all_successful;
}

bool make::write_makefile(const std::string& project_name, int cxx_standard) {
    std::ofstream makefile("Makefile");

    if(!makefile)   return false;
    std::string MAKEFILE_BOILERPLATE_(MAKEFILE_BOILERPLATE);
    util::replace_all(MAKEFILE_BOILERPLATE_, TAG_PROJECT_NAME, project_name);
    util::replace_all(MAKEFILE_BOILERPLATE_, TAG_CXX_STANDARD, std::to_string(cxx_standard));

    makefile << MAKEFILE_BOILERPLATE_;
    makefile.close();
    return true;
}

bool make::write_workflow(const std::string& project_name) {
    std::filesystem::create_directories(".github/workflows");

    std::ofstream workflow(".github/workflows/build.yml");

    if(!workflow)   return false;
    std::string MAKE_WORKFLOW_BOILERPLATE_(MAKE_WORKFLOW_BOILERPLATE);
    util::replace_all(MAKE_WORKFLOW_BOILERPLATE_, TAG_PROJECT_NAME,
                    project_name);
    workflow << MAKE_WORKFLOW_BOILERPLATE_;

    workflow.close();
    return true;
}

bool make::write_readme(const std::string& project_name, int cxx_standard, const std::string &project_desc) {
    std::ofstream readme("README.md");

    if(!readme) return false;
    std::string README_BOILERPLATE_ = README_CMAKE_BOILERPLATE;

    util::replace_all(README_BOILERPLATE_, TAG_PROJECT_NAME, project_name);
    util::replace_all(README_BOILERPLATE_, TAG_PROJECT_DESC, project_desc);
    util::replace_all(README_BOILERPLATE_, TAG_CXX_STANDARD,
                    std::to_string(cxx_standard));

    readme << README_BOILERPLATE_;

    readme.close();
    return true;
}

bool make::build_project(BuildType build_type) {
    using std::filesystem::exists;

    if (exists("Makefile")) {
        std::system("make");

        return true;
    } else
        return false;
}
