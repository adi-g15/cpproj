#pragma once

#include <yaml/Yaml.hpp>

#include <string>
#include <optional>
#include <filesystem>
#include <fstream>
#include <map>

#include <rang.hpp>

#include "configurations.hpp"

using std::optional, std::filesystem::exists;
namespace dependency_mngr {
    std::map<std::string, std::string> dependency_database;

    // pre-condition: GLOBAL_CONFIG_LOCATION exists
    inline void init_dep_db() {    // initialise the dependency database
        Yaml::Node yaml_tree;
        Yaml::Parse(yaml_tree, GLOBAL_CONFIG_LOCATION);

        if( yaml_tree.IsSequence() ) {
            std::cerr << rang::fg::red
                      << "[ERROR] Dependency database (all_dep.yml) is invalid"
                      << "        The all_dep.yml file should have each dependency in it's own block\n"
                      << rang::fg::reset;
        }

        for(auto iter = yaml_tree.Begin(); iter != yaml_tree.End(); iter++) {
            dependency_database.insert({
                (*iter).first,
                (*iter).second.As<std::string>()
                });
        }
    }

    inline optional<std::string> get_dependency_url(const std::string& name) {
        if( exists(GLOBAL_CONFIG_LOCATION) && dependency_database.empty()) {
    		init_dep_db();
        }

        auto iter = dependency_database.find(name);
        if(iter != dependency_database.end()){
            return dependency_database[name];
        } else return std::nullopt;
    }

    inline void print_all() {
        // @todo
    }
}
