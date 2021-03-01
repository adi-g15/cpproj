#include "git_connect.hpp"

#include <rang.hpp>
#include <util/system.hpp>

#include <filesystem>
#include <iostream>

bool git_connect::init_git_repo() {}

bool git_connect::init_git_repo(const std::filesystem::path &path) {
    using std::filesystem::current_path;

    auto original_path = current_path();
    current_path(path);

    init_git_repo();

    current_path(original_path);
}

std::optional<GIT_REF> git_connect::get_current_ref() {
    using std::filesystem::exists;

    // auto original_git_dir = std::getenv("GIT_DIR");
    // auto env = "GIT_DIR=" + project_name + "/.git";
    // putenv(env.data());
    // if (original_git_dir != nullptr)
    // 	putenv(("GIT_DIR=" + std::string(original_git_dir))
    // 				.data()); // resetting the GIT_DIR environment
    // variable auto ref = std::filesystem::current_path().string();

    // auto [ref, was_success] = exec_command("git rev-parse HEAD");
    auto ref = util::exec("git rev-parse HEAD");

    if (!exists(".git")) {
        std::cerr << "[ERROR] This directory may not a valid git repo... Or "
                     "git rev-parse HEAD may fail to execute";
        return std::nullopt;
    }

    GIT_REF our_ref;

    if (ref.back() == '\n')
        ref.pop_back();
    if (ref.size() != our_ref.size()) {
        std::cout << rang::fg::red
                  << "[ERROR] Getting latest commit ref failed! "
                  << rang::fg::reset
                  << "\nSome submodule may not have been cloned, skipping "
                     "rather than exiting...\n";

        return std::nullopt;
    }

    std::copy(ref.begin(), ref.end(), our_ref.begin());

    return our_ref;
}

std::optional<GIT_REF>
git_connect::get_current_ref(const std::filesystem::path &path) {

    using std::filesystem::current_path;

    auto original_path = current_path();
    get_current_ref();

    auto ref = get_current_ref();

    current_path(original_path);

    return ref;
}
