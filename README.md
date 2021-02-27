CPProj
----

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

## Future

* Atleast some dependency handling (not management, the project's not targetting for that now, simple, you pass an argument, if Find* can find it add it then to CMakeLists)
* msbuild starter boilerplate

:copyright: Aditya Gupta 2021

