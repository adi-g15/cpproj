#pragma once

#include "options.hpp"

#include <cxxopts.hpp>

#include <string>

namespace cpproj {
    // using options_handler::set_options;

    namespace _impl
    {
        std::string get_name(const cxxopts::ParseResult&);
    } // namespace impl
}
