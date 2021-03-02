#pragma once

#include "enums.hpp"
#include "git_connect.hpp"
#include "options.hpp"

#include <cxxopts.hpp>

#include <optional>
#include <string>
#include <string_view>
#include <utility> // for std::pair

using std::optional;

struct cpproj_data {
    std::string PROJECT_NAME;
    int PROJECT_CXX_STANDARD = 17;
    std::string PROJECT_BUILD_MNGR = "cmake";
    bool PROJECT_USE_GIT = true;

    bool ERR_BIT = false;
    bool SHOW_HELP = false;

    bool BUILD_IT = false;
    BuildType BUILD_TYPE = BuildType::Debug;
    bool EXECUTE = false;
    std::string EXECUTABLE_NAME;
};

struct Dependency {
    std::string name;
    optional<GIT_REF> ref;
    std::string url;

    Dependency(const std::string &name, decltype(ref) &ref, const std::string &)
        : name(name), ref(ref), url(url) {}
};

struct ConfigYaml {
    std::string_view PROJECT_NAME;
    std::string DESCRIPTION;
    std::vector<Dependency> dependencies;
};

using std::optional;
namespace cpproj {
void init(cxxopts::Options &options);
cpproj_data parse(cxxopts::Options &options, int argc, const char *argv[]);
using option_handler::show_help;
void config_writer(const ConfigYaml &config);

namespace _impl {
using option_handler::debug_result;
using option_handler::set_options;
optional<GIT_REF> add_dep_submodule(const std::string &name,
                                    const std::string &url);
std::string get_name(const cxxopts::ParseResult &);
int standard_str_to_num(const std::string &std_name);

} // namespace _impl
} // namespace cpproj
