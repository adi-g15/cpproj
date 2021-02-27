CPProj
----

[![Build Status](https://github.com/adi-g15/cpproj/actions/workflows/build.yml/badge.svg)](https://github.com/adi-g15/cpproj/actions/workflows/build.yml)

A C++ project management tool. Inspired from cargo.

For now, i am just trying to replicating the functionalities,
so I can get started with new projects fairly quickly, ie. 
it won't do anything much smart, mostly just creating a boilerplate.
And is intended to be usable offline, as most are, instead of cloning an online repo.

## Dependencies

To make my work faster, i used:

* [cxxopts](https://github.com/jarro2783/cxxopts) - Lightweight C++ command line option parser

## Building

```
mkdir build && cd build
cmake ..
cmake --build .
```

## Installing

> Build Release build, then cmake --install

```sh
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
cmake --install .    # this one may require admin privelage
```

Then access from anywhere by using the command `cpproj`

## Usage

```
A C++ project management tool. Inspired from cargo.
Usage:
  cpproj [OPTION...]

      --name arg       Name of project (mentioning --name can be skipped)
      --std arg        C++ standard to use (11,14,17,20,..., default is 
                       c++17)
      --no-git         DON'T initialise a repo, default is a git repo is 
                       also created in the project)
      --build_sys arg  make or cmake, build system or generator, default is 
                       cmake (default: cmake)
  -B, --build          Build the project
  -R, --run            Build and Run the executable
      --exec arg       Executable name (this is not required, and is used 
                       only by `cpproj run`)
  -h, --help           Show help
```

**Examples**

* `cpproj my_project` or `cpproj --name my_project`  (both same)
* `cpproj my_project --no-git`    (without a git repo)
* `cpproj my_project --build_sys make`
* `cpproj my_project --std 14`    (builds a CMake project)
* `cpproj --build`                (inside a project or it's build directory)
* `cpproj --run`                  (also builds the project)

> Irrespective of order of arguments, and all above can be combined in any order

## Future

* Atleast some dependency handling (not management, the project's not targetting for that now, simple, you pass an argument, if Find* can find it add it then to CMakeLists)
* msbuild starter boilerplate

:copyright: Aditya Gupta 2021

