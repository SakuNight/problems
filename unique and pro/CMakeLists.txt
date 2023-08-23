# cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=g++-12 -DCMAKE_EXPORT_COMPILE_COMMANDS=On -S . -B build

cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 20)

project(unique_and_pro)

add_executable(std std.cpp)
add_executable(bf bf.cpp)
add_executable(gen gen.cpp)