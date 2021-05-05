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

struct action {

};

struct cpproj_data {
    std::string PROJECT_NAME;
    std::string DESCRIPTION;
    int PROJECT_CXX_STANDARD = 17;
    std::string PROJECT_BUILD_MNGR = "cmake";
    bool PROJECT_USE_GIT = true;

    bool ERR_BIT = false;
    bool SHOW_HELP = false;

    bool BUILD_IT = false;
    BuildType BUILD_TYPE = BuildType::Debug;
    bool EXECUTE = false;
    std::string EXECUTABLE_NAME;

    bool CREATE_CONFIG = true;
    bool UPDATE_CONFIG = false; // pre-condition to be true: project already created
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
    std::string_view DESCRIPTION;
    std::vector<Dependency> dependencies;
};

using std::optional;
namespace cpproj {
    cxxopts::ParseResult init(cxxopts::Options &options, int argc, const char* argv[]);
    cpproj_data parse(cxxopts::Options &options, const cxxopts::ParseResult& result);
    using option_handler::show_help;
    void create_config(const cpproj_data&, const cxxopts::ParseResult&);
    void update_config(const cxxopts::ParseResult&);

    namespace _impl {
        using option_handler::debug_result;
        using option_handler::set_options;
        optional<GIT_REF> add_dep_submodule(const std::string &name,
                                            const std::string &url);
        std::string get_name(const cxxopts::ParseResult &);
        int standard_str_to_num(const std::string &std_name);
        void config_writer(const ConfigYaml &config);
        void append_dependencies(const std::vector<Dependency>& dependencies);

    } // namespace _impl
} // namespace cpproj
