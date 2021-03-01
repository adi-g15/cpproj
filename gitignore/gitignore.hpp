#pragma once

#include "C++.boilerplate.hpp"
#include "CMake.boilerplate.hpp"
#include "VisualStudioCode.boilerplate.hpp"

#include <vector>
#include <fstream>

enum class GITIGNORE_FLAGS {
    CPP_GENERAL,
    CMAKE,
    VS_CODE,
    VISUAL_STUDIO
};

namespace gitignore
{
    void create_gitignore(const std::vector<GITIGNORE_FLAGS>& flags) {
        std::ofstream file(".gitignore");

        for (auto &&flag : flags)
        {
            switch (flag)
            {
            case GITIGNORE_FLAGS::CMAKE :
                file << CMAKE_GITIGNORE << '\n';
                break;
            case GITIGNORE_FLAGS::CPP_GENERAL :
                file << CPP_GITIGNORE << '\n';
                break;
            case GITIGNORE_FLAGS::VISUAL_STUDIO :
            case GITIGNORE_FLAGS::VS_CODE :
                file << VS_CODE_GITIGNORE << '\n';
                break;
            default:
                break;
            }
        }

        file.close();
    }
}

