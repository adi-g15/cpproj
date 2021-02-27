#pragma once

#include <string>
#include <string_view>

#include <util/string.hpp>

#include <cxxopts.hpp>

static constexpr auto TAG_PROJECT_NAME = "${{CPPROJ_PROJECT_NAME}}";
static constexpr auto TAG_CXX_STANDARD = "${{CPPROJ_CXX_STANDARD}}";

// auto show_help(auto options) { // available with Concepts
auto show_help(const cxxopts::Options &options) {
    std::cout << options.help() << '\n';
}

/**
 * @brief - Converts standard name in string to a number
 *
 * ie. for `c++17` it returns 17
 *
 * @exception: When the string name isn't valid, ie. starting with c++... or
 * directly an integer eg. "17", then throws an exception
 */
int standard_str_to_num(const std::string &std_name) {
    std::string_view standard_str(std_name);
    if (util::starts_with(std_name, "c++")) {
        standard_str.remove_prefix(
            std::size("c++")); // WILL NOT BE UNDEFINED BEHAVIOUS, since string
                               // already atleast of 3 length
    }

    // by now, the string MUST ONLY contain an integer
    return std::stoi(standard_str.data());
}
