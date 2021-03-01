#pragma once

#include <filesystem>
#include <array>
#include <optional>
#include "system_call.hpp"

typedef std::array<char, 40> GIT_REF;

// @note - Currently using system calls, instead of libraries like libgit2, since only bare functionality was needed initially
namespace git_connect {
    bool init_git_repo();   // initialises a git repo in current directory
    bool init_git_repo(const std::filesystem::path&);   // initialises a git repo at the target directory

    std::optional<GIT_REF> get_current_ref(); // returns the current (ie. latest, for newly initialised project) commit's ref
    std::optional<GIT_REF> get_current_ref(const std::filesystem::path&);
}
