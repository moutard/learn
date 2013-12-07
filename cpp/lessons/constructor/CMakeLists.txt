cmake_minimum_required(VERSION 2.6)
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
add_executable(
  runTests
  wall.h
  wall.cpp
  brick.h
  brick.cpp
  house.h
  tests.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

# Link runTests with what we want to test and the GTest and pthread library
add_executable(
  runMain
  wall.h
  wall.cpp
  main.cpp)

