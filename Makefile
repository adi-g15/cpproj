cpproj: src/main.cpp includes/cmake.hpp includes/common.hpp includes/make.hpp includes/options.hpp
	g++ -g src/main.cpp -Iincludes -I. -Iext/cxxopts/include -Iext/rang/include -Iext/utilpp/includes -o cpproj -std=c++17 -lstdc++fs

clean:
	rm -f cpproj
