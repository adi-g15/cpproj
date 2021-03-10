CPProj
----

[![Build Status](https://github.com/adi-g15/cpproj/actions/workflows/build_windows.yml/badge.svg)](https://github.com/adi-g15/cpproj/actions/workflows/build_windows.yml)

A C++ project management tool. Inspired from cargo.

For now, i am just trying to replicating the functionalities,
so I can get started with new projects fairly quickly, ie. 
it won't do anything much smart, mostly just creating a boilerplate.
And is intended to be usable offline, as most are, instead of cloning an online repo.

> *Note*: There's another tool named [build2](https://www.build2.org). I got to know it recently (after this project completed its basic form).
>  You may still chose to use cpproj, for its simplicity, and being much smaller and much faster to build

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

      --name arg       Name of project (can be passed directly too, without 
                       mentioning --name)
      --desc arg       Brief description
      --std arg        C++ standard to use (11,14,17,20,..., default is 
                       c++17)
      --no-git         DON'T initialise a repo, default is a git repo is 
                       also created in the project)
      --build_sys arg  make or cmake, build system or generator, default is 
                       cmake (default: cmake)
  -B, --build          Build the project
      --release        flag for a Release build
  -R, --run            Build and Run the executable
      --exec arg       Executable name (this is not required, and is used 
                       only by `cpproj run`)
  -h, --help           Show help
  -D, --add-dep arg    Add a dependency to ext/ directory
      --sync-dep       Sync all dependency submodules, according to 
                       .cpproj.yml
      --use-fetch      use CMake's FetchContent API (adds to 
                       CMakeLists.txt)
      --no-config      don't create the .cpproj.yml config file
```

**Examples**

* `cpproj my_project` or `cpproj --name my_project`  (both same)
* `cpproj my_project --no-git`    (without a git repo)
* `cpproj my_project --build_sys make`
* `cpproj my_project --std 14`    (builds a CMake project)
* `cpproj --build`                (inside a project or it's build directory)
* `cpproj --run`                  (also builds the project)
* `cpproj --add-dep=utilpp,graphMat`                  (add dependencies to the project)

> Basic Dependency Handling
  Use the --add-dep to pass the dependencies as array or several --add-dep flags

  Say you want to use the awesome graphMat and utilpp libraries, you don't have to know the repo link, etc. to submodule it

```sh
  # Example Workflow
  cpproj asor

  # DONE, you have a complete project, which also has a github action, to check build status at each push :tada:

  # Edit files
  cpproj -R   # build and execute it

  cpproj --add-dep=utilpp,graphMat
```

> Irrespective of order of arguments, and all above can be combined in any order

## Todo

* Adding the cloned dependencies in CMakeLists(includes or sub_directory)
* List all available dependencies with brief description
* msbuild starter boilerplate

:copyright: Aditya Gupta 2021

