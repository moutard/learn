cmake_minimum_required(VERSION 2.6)
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
# Link runTests with what we want to test and the GTest and pthread library
add_executable(
  runTests
  maze.h
  maze.cpp
  microsoft_tests.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

add_executable(
  runMain
  maze.h
  maze.cpp
  main.cpp)

add_executable(
  runExample
  grid_array.h
  grid_array.cpp
  main_example.cpp)
