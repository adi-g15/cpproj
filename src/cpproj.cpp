#include "cpproj.hpp"
#include "dep_mngr.hpp"
#include "common.hpp"

#include <rang.hpp>
#include <util/string.hpp>

#include <set>
#include <string>
#include <string_view>

void cpproj::init(cxxopts::Options& options) {
    _impl::set_options(options); // set supported operationsons();
}

cpproj_data cpproj::parse(cxxopts::Options& options, int argc, const char* argv[]) {
    cpproj_data pData;  // project_data
    auto& PROJECT_NAME          = pData.PROJECT_NAME;
    auto& PROJECT_CXX_STANDARD  = pData.PROJECT_CXX_STANDARD;
    auto& PROJECT_BUILD_MNGR    = pData.PROJECT_BUILD_MNGR;
    auto& PROJECT_USE_GIT       = pData.PROJECT_USE_GIT;
    auto& ERR_BIT               = pData.ERR_BIT;
    auto& SHOW_HELP             = pData.SHOW_HELP;

    const auto &result = options.parse(argc, argv);
    const auto &unmatched_args = result.unmatched();

    if (argc == 1 || result.count("help") > 0) {
        SHOW_HELP = true;
    } else if (result.count("build") > 0) {
        pData.BUILD_IT = true;
    } else if (result.count("run") > 0) {
        pData.EXECUTE = true;
        pData.EXECUTABLE_NAME = result.count("exec") > 0
                            ? result["exec"].as<std::string>()
                            : "";
    }

    PROJECT_NAME = cpproj::_impl::get_name(result); // will be moved inside cpproj later

    if (PROJECT_NAME.empty() && result.count("build") == 0 &&
        result.count("run") == 0) {
        ERR_BIT = true;
    }

    PROJECT_CXX_STANDARD =
        result.count("std") > 0
            ? _impl::standard_str_to_num(result["std"].as<std::string>())   // i will move it later to another component likely
            : 17;
    PROJECT_BUILD_MNGR = result.count("build_sys") > 0
                                ? result["build_sys"].as<std::string>()
                                : "cmake";
    PROJECT_USE_GIT =
        result.count("no-git") > 0 ? !result["no-git"].as<bool>() : true;

    switch (PROJECT_CXX_STANDARD) {
        case 98:
        case 11:
        case 14:
        case 17:
        case 20:
            break;
        default:
            std::cout << "Warning: Invalid C++ standard passed: "
                    << PROJECT_CXX_STANDARD << "Defaulting to C++17\n";
            PROJECT_CXX_STANDARD = 17;
            break;
    }

    if(!(PROJECT_BUILD_MNGR == "cmake" || PROJECT_BUILD_MNGR == "make")) {
        std::cout << "[Warning] " << pData.PROJECT_BUILD_MNGR
                        << " not supported\n";

        PROJECT_BUILD_MNGR = "cmake";
    }

    ConfigYaml config_yaml;
    config_yaml.PROJECT_NAME = PROJECT_NAME;
    if(result.count("desc") > 0)
        config_yaml.DESCRIPTION  = result["desc"].as<std::string>();

    if(result.count("add-dep") > 0) {
        bool all_ref_known = true; // could get the latest refs of all submodules; required to show a warning at end
        for (auto &&dep_name : result["add-dep"].as<std::vector<std::string>>() )
        {
            auto dep_url = dependency_mngr::get_dependency_url(dep_name);
            if(!dep_url) {
                std::cerr << rang::fg::yellow
                          << "[WARNING] \"" << dep_name << "\" can't be resolved to a url\n"
                          << rang::fg::reset;

                continue;
            }

            auto dep_ref = _impl::add_dep_submodule(dep_name, dep_url.value());
            if(!dep_ref) {
                std::cerr << rang::fg::yellow
                          << "[WARNING] \"" << dep_name << "\": Can't get latest ref\n"
                          << rang::fg::reset;

                all_ref_known = false;
            }

            config_yaml.dependencies.emplace_back(
                dep_name,
                dep_ref,
                dep_url.value()
            );
        }


        if(all_ref_known)
            std::clog << rang::fg::yellow
                        << "You may need to add it yourself to .cpproj.yml (if using), get the ref using `git rev-parse HEAD` inside the submodule directory\n"
                        << rang::fg::reset;

    }

    if(result.count("use-fetch") > 0 && result["use-fetch"].as<bool>()) {
        // @todo - Using CMake's FetchContent API
    }

    if(result["no-config"].as<bool>() == false)
        cpproj::config_writer(config_yaml);

    return pData;
}

std::string cpproj::_impl::get_name(const cxxopts::ParseResult& result) {
    using string_ref = std::string_view; /*std::reference_wrapper<std::string>>*/;

    std::string project_name;
    std::set<string_ref> used_args;

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

/**
 * @brief - Converts standard name in string to a number
 *
 * ie. for `c++17` it returns 17
 *
 * @exception: When the string name isn't valid, ie. starting with c++... or
 * directly an integer eg. "17", then throws an exception
 */
int cpproj::_impl::standard_str_to_num(const std::string &std_name) {
    std::string_view standard_str(std_name);
    if (util::starts_with(std_name, "c++")) {
        standard_str.remove_prefix(
            std::size("c++")); // WILL NOT BE UNDEFINED BEHAVIOUS, since string
                               // already atleast of 3 length
    }

    // by now, the string MUST ONLY contain an integer
    return std::stoi(standard_str.data());
}

optional<GIT_REF> cpproj::_impl::add_dep_submodule(const std::string& name, const std::string& url) {
    using std::filesystem::create_directory, std::filesystem::current_path;
    constexpr bool use_depth_one = true;

    create_directory(EXTERNAL_DEPENDENCY_DIR);

    current_path("ext/");

    std::system(( "git submodule add " + url + " " + name + (use_depth_one ? "--depth=1": "") ).data());
    auto ref = git_connect::get_current_ref();

    current_path("../");

    return ref;
}

void cpproj::config_writer(const ConfigYaml& config) {
    // @todo
}
