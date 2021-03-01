#include <cxxopts.hpp>

namespace option_handler {
    void set_options(cxxopts::Options &options) {
        options.add_options()("name",
                            "Name of project (can be passed directly too, "
                            "without mentioning --name)",
                            cxxopts::value<std::string>());
        options.add_options()(
            "std", "C++ standard to use (11,14,17,20,..., default is c++17)",
            cxxopts::value<std::string>()); // can be string or a simple number
        options.add_options()("no-git",
                            "DON'T initialise a repo, default is a git repo is "
                            "also created in the project)",
                            cxxopts::value<bool>());
        options.add_options()(
            "build_sys",
            "make or cmake, build system or generator, default is cmake",
            cxxopts::value<std::string>()->default_value("cmake"));
        options.add_options()
                            ("B,build", "Build the project")
                            ("release", "flag for a Release build");
        options.add_options()("R,run", "Build and Run the executable");
        options.add_options()("exec",
                            "Executable name (this is not required, and is used "
                            "only by `cpproj run`)",
                            cxxopts::value<std::string>());
        options.add_options()("h,help", "Show help");
    }

    // auto show_help(auto options) { // available with Concepts
    auto show_help(const cxxopts::Options &options) {
        std::cout << options.help() << '\n';
    }

    auto debug_result(const cxxopts::ParseResult &result) {
        std::clog << "Arguments: ";
        for (const auto &arg : result.arguments()) {
            std::cout << arg.key() << " -> " << arg.value() << '\n';
        }

        std::clog << "Unmatched: \n";
        std::copy(result.unmatched().begin(), result.unmatched().end(),
                std::ostream_iterator<std::string>(std::cout, ", "));
        std::cout << std::endl;
    }
}

using option_handler::set_options;
using option_handler::show_help;
