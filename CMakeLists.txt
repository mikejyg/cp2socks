cmake_minimum_required(VERSION 2.8)

project(cp2socks CXX C)

add_compile_options(--std=c++11 -Wall)

include_directories(include mgucc/include)

file(GLOB_RECURSE srcs src/*.cpp testSrc/*.cpp)
add_executable(cp2socks ${srcs})
target_link_libraries(cp2socks pthread)
