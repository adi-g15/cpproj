#pragma once

#include "options.hpp"

#include <cxxopts.hpp>

#include <string>
#include "enums.hpp"

struct cpproj_data {
    std::string PROJECT_NAME;
    int         PROJECT_CXX_STANDARD = 17;
    std::string PROJECT_BUILD_MNGR = "cmake";
    bool        PROJECT_USE_GIT = true;

    bool        ERR_BIT = false;
    bool        SHOW_HELP = false;

    bool        BUILD_IT = false;
    BuildType   BUILD_TYPE = BuildType::Debug;
    bool        EXECUTE = false;
    std::string EXECUTABLE_NAME;
};

namespace cpproj {
    void        init(cxxopts::Options& options);
    cpproj_data parse(cxxopts::Options& options, int argc, const char* argv[]);
    using option_handler::show_help;

    namespace _impl
    {
        using option_handler::debug_result;
        using option_handler::set_options;
        std::string get_name(const cxxopts::ParseResult&);
        int standard_str_to_num(const std::string &std_name);

    } // namespace impl
}
