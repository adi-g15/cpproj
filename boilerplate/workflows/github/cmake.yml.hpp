#pragma once

constexpr auto CMAKE_ACTION_BOILERPLATE = 
                    "name: CMake Build\n"
                    "\n"
                    "on: [push,pull_request]\n"
                    "\n"
                    "env:\n"
                    "  BUILD_TYPE: Release\n"
                    "\n"
                    "jobs:\n"
                    "  release:\n"
                    "    runs-on: ${{ matrix.os }}\n"
                    "    strategy:\n"
                    "      matrix:\n"
                    "        os: [ubuntu-latest,windows-latest]  # if you only want to build on one, remove the other os\n"
                    "\n"
                    "    steps:\n"
                    "    - uses: actions/checkout@v2\n"
                    "      with:\n"
                    "        submodules: recursive\n"
                    "\n"
                    "    - name: Create Build Environment\n"
                    "      run: cmake -E make_directory ${{github.workspace}}/build\n"
                    "\n"
                    "    - name: Configure\n"
                    "      shell: bash\n"
                    "      working-directory: ${{github.workspace}}/build\n"
                    "      run: cmake $GITHUB_WORKSPACE -DCMAKE_BUILD_TYPE=$BUILD_TYPE\n"
                    "\n"
                    "    - name: Build\n"
                    "      working-directory: ${{github.workspace}}/build\n"
                    "      shell: bash\n"
                    "      run: cmake --build . --config $BUILD_TYPE   # --config option for MSVC\n"
                    "\n"
                    "#     - name: Test\n"
                    "#       working-directory: ${{github.workspace}}/build\n"
                    "#       shell: bash\n"
                    "#       # Execute tests defined by the CMake configuration.  \n"
                    "#       # See https://cmake.org/cmake/help/latest/manual/ctest.1.html for more detail\n"
                    "#       run: ctest -C $BUILD_TYPE\n"
                    "\n";
