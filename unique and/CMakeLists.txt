# cmake -G Ninja -B build -S . -DCMAKE_CXX_COMPILER=g++-12 -DCMAKE_EXPORT_COMPILE_COMMANDS=On -DCMAKE_BUILD_TYPE=Debug
# Used to generate compile_commands.json

cmake_minimum_required(VERSION 3.0)

project(unique_and)

set(CMAKE_CXX_STANDARD 20)

add_executable(std std.cpp)
add_executable(brute_force brute_force.cpp)
add_executable(makedata makedata.cpp)