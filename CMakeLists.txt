cmake_minimum_required(VERSION 3.5)
project(TapeSimulator VERSION 0.1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_compile_options(-Wall -Wextra -Wpedantic -g -std=c++2a)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(TapeLib
    src/TapeSimulator.cpp
    src/Logs.cpp
    src/Sort.cpp
    src/Config.cpp)

add_executable(TapeSorter src/main.cpp)
target_link_libraries(TapeSorter TapeLib)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(
  test_sort
  src/test.cpp
)
target_link_libraries(
    test_sort
    GTest::gtest_main
    TapeLib
)

include(GoogleTest)
gtest_discover_tests(test_sort)
