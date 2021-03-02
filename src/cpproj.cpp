#include "cpproj.hpp"

#include <set>

std::string cpproj::_impl::get_name(const cxxopts::ParseResult& result) {
    std::string project_name;
    std::set<std::string> used_args;

    for (const auto &arg : result.arguments()) {
        used_args.insert(arg.value());
    }

    if (result.count("name") > 0)
        project_name = result["name"].as<std::string>();

    for (const auto &arg : result.unmatched()) {
        if (used_args.find(arg) ==
            used_args
                .end()) { // first unmatched argument is considered the name
            project_name = arg;
            break;
        }
    }

    return project_name;
}