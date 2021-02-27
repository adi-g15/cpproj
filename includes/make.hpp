#pragma once

#include <filesystem>
#include <string>

#include "common.hpp"

#include "boilerplate/github_workflow.boilerplate.hpp"
#include "boilerplate/main.boilerplate.hpp"
#include "boilerplate/makefile.boilerplate.hpp"
#include "boilerplate/readme.boilerplate.hpp"

#include "gitignore/C++.boilerplate.hpp"

using namespace std::filesystem;

// wanted to use std::32string, but writing the widen is not so simple
bool generate_make_project(const std::string &project_name, int cxx_standard,
                           bool use_git) {
    char ch;
    std::clog << "Working Directory: " << current_path() << '\n';
    if (exists(project_name)) {
        std::cout << "\n\n"
                  << project_name << "/ already exists! Chose one option: \n"
                  << "[Y|y] Delete original folder\n"
                  << "[N|n] Don't change anything\n"
                  << "[O|o] Overwrite conflicting files\n Enter your choice : ";

        std::cin >> ch;

        switch (ch) {
        case 'Y':
        case 'y':
            std::clog << "Removed " << project_name << "/\n";
            remove_all(project_name);
        case 'O':
        case 'o':
            break; // continue with the function
        case 'N':
        case 'n':
        default:
            return false;
        }
    }

    create_directories(project_name + "/src");
    create_directories(project_name + "/include");
    create_directories(project_name + "/.github/workflows/");

    std::ofstream Makefile(project_name + "/Makefile");
    std::ofstream MakeWorkflow(project_name + "/.github/workflows/build.yml");
    std::ofstream main_cpp(project_name + "/src/main.cpp");

    std::string MAKEFILE_BOILERPLATE_(MAKEFILE_BOILERPLATE),
        MAKE_WORKFLOW_BOILERPLATE_(MAKE_WORKFLOW_BOILERPLATE),
        MAIN_CPP_BOILERPLATE_(MAIN_CPP_BOILERPLATE);

    util::replace_all(MAKEFILE_BOILERPLATE_, TAG_PROJECT_NAME, project_name);
    util::replace_all(MAKE_WORKFLOW_BOILERPLATE_, TAG_PROJECT_NAME,
                      project_name);
    util::replace_all(MAIN_CPP_BOILERPLATE_, TAG_PROJECT_NAME, project_name);
    util::replace_all(MAIN_CPP_BOILERPLATE_, TAG_PROJECT_NAME, project_name);

    Makefile << MAKEFILE_BOILERPLATE_;
    MakeWorkflow << MAKE_WORKFLOW_BOILERPLATE_;
    main_cpp << MAIN_CPP_BOILERPLATE_;

    main_cpp.close();
    MakeWorkflow.close();
    Makefile.close();

    if (use_git) {
        std::ofstream readme(project_name + "/README.md");
        std::ofstream gitignore(project_name + "/.gitignore");

        std::string README_BOILERPLATE_ = README_CMAKE_BOILERPLATE;

        util::replace_all(README_BOILERPLATE_, TAG_PROJECT_NAME, project_name);
        util::replace_all(README_BOILERPLATE_, TAG_CXX_STANDARD,
                          std::to_string(cxx_standard));

        gitignore << CPP_GITIGNORE << '\n';
        readme << README_BOILERPLATE_;

        gitignore.close();
        readme.close();

        // @note - I had to go with a system call, if git provides a better way
        // please tell if you know, i will try to find some when i come back to
        // this project
        auto original_git_dir = std::getenv("GIT_DIR");
        auto env = "GIT_DIR=" + project_name + "/.git";
        putenv(env.data());
        create_directory(project_name + "/.git");
        std::system(
            "git init"); // initialises the repo in the project directory
        if (original_git_dir != nullptr)
            putenv(("GIT_DIR=" + std::string(original_git_dir))
                       .data()); // resetting the GIT_DIR environment variable
    }

    return true;
}

bool build_make_proj() {
    if(exists("Makefile")) {
        std::system("make");

        return true;
    } else return false;
}
