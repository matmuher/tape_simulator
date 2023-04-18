cmake_minimum_required(VERSION 3.5)
project(TapeSimulator VERSION 0.1)


# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_compile_options(-Wall -Wextra -Wpedantic -g -std=c++2a)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(TapeSorter
                src/main.cpp
                src/TapeSimulator.cpp
                src/Logs.cpp
                src/Sort.cpp)
