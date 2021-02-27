#pragma once

#include <string>
#include <filesystem>
#include <fstream>
#include <cstdlib>

#include "common.hpp"

#include "boilerplate/cmakelists.boilerplate.hpp"
#include "boilerplate/github_workflow.boilerplate.hpp"
#include "boilerplate/main.boilerplate.hpp"
#include "boilerplate/readme.boilerplate.hpp"

#include "gitignore/C++.boilerplate.hpp"
#include "gitignore/CMake.boilerplate.hpp"
#include "gitignore/VisualStudioCode.boilerplate.hpp"

#include <util/string.hpp>

using namespace std::filesystem;

// wanted to use std::32string, but writing the widen is not so simple
bool generate_cmake_project(const std::string& project_name, int cxx_standard, bool use_git ) {
    char ch;
    std::clog << "Working Directory: " << current_path() << '\n';
    if( exists(project_name) ) {
        std::cout << "\n\n" << project_name << "/ already exists! Chose one option: \n"
                    << "[Y|y] Delete original folder\n"
                    << "[N|n] Don't change anything\n"
                    << "[O|o] Overwrite conflicting files\n Enter your choice : ";

        std::cin >> ch;

        switch (ch)
        {
        case 'Y':
        case 'y':
            std::clog << "Removed " << project_name << "/\n";
            remove_all(project_name);
        case 'O':
        case 'o':
            break;  // continue with the function
        case 'N':
        case 'n':
        default:
            return false;
        }
    }

    create_directories( project_name + "/src");
    create_directories( project_name + "/include");

    std::ofstream CMakeLists(project_name + "/CMakeLists.txt");
    std::ofstream main_cpp(project_name + "/src/main.cpp");

    std::string CMAKELISTS_BOILERPLATE_( CMAKELISTS_BOILERPLATE ),
                MAIN_CPP_BOILERPLATE_( MAIN_CPP_BOILERPLATE );

    util::replace_all(CMAKELISTS_BOILERPLATE_, TAG_PROJECT_NAME, project_name);
    util::replace_all(CMAKELISTS_BOILERPLATE_, TAG_CXX_STANDARD, std::to_string(cxx_standard) );
    util::replace_all(MAIN_CPP_BOILERPLATE_, TAG_PROJECT_NAME, project_name);
    util::replace_all(MAIN_CPP_BOILERPLATE_, TAG_PROJECT_NAME, project_name);

    CMakeLists      << CMAKELISTS_BOILERPLATE_;
    main_cpp        << MAIN_CPP_BOILERPLATE_;

    main_cpp.close();
    CMakeLists.close();

    if(use_git) {
        create_directories( project_name + "/.github/workflows/");
        std::string CMAKE_WORKFLOW_BOILERPLATE_( CMAKE_WORKFLOW_BOILERPLATE );

        std::ofstream readme(project_name + "/README.md");
        std::ofstream gitignore(project_name + "/.gitignore");
        std::ofstream CMakeWorkflow(project_name + "/.github/workflows/build.yml");

        std::string README_BOILERPLATE_ = README_CMAKE_BOILERPLATE;
        util::replace_all(CMAKE_WORKFLOW_BOILERPLATE_, TAG_PROJECT_NAME, project_name);
        util::replace_all(README_BOILERPLATE_, TAG_PROJECT_NAME, project_name );
        util::replace_all(README_BOILERPLATE_, TAG_CXX_STANDARD, std::to_string(cxx_standard) );

        CMakeWorkflow   << CMAKE_WORKFLOW_BOILERPLATE_;
        gitignore       << VS_CODE_GITIGNORE << '\n' << CPP_GITIGNORE << '\n' << CMAKE_GITIGNORE << '\n';
        readme          << README_BOILERPLATE_;

        CMakeWorkflow.close();
        gitignore.close();
        readme.close();

        // @note - I had to go with a system call, if git provides a better way please tell if you know, i will try to find some when i come back to this project
        auto original_git_dir = std::getenv("GIT_DIR");
        auto env = "GIT_DIR=" + project_name + "/.git";
        putenv(env.data());
        create_directory(project_name + "/.git");
        std::system("git init");    // initialises the repo in the project directory
        if( original_git_dir != nullptr )   putenv(("GIT_DIR=" + std::string(original_git_dir)).data());    // resetting the GIT_DIR environment variable
    }

    return true;
}
