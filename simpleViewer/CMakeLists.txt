cmake_minimum_required (VERSION 2.6)
project (SimpleViewer)

# Locate GTest
#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})

# Locate libQGLViewer
# as libQGLViewer is an external library that CMake doesn't yet have modules for
# we need to create a module by ourselves.
# We created a folder called cmake/Modules in our source directory root.
# we add this file in it https://raw.github.com/RainerKuemmerle/g2o/master/cmake_modules/FindQGLViewer.cmake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# See more on how add Qt with cmake here:
# http://qt-project.org/quarterly/view/using_cmake_to_build_qt_projects
# libqglviewer se Qt so see how we included it in findQGLViewer.cmake

find_package(QGLViewer REQUIRED)
#include_directories(${QGLViewer_INCLUDE_DIRS})

# Create executable called simpleViewer
add_executable(
  simpleViewer
  simpleViewer.h
  simpleViewer.cpp
  main.cpp)

# Add target link library
#target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
target_link_libraries(simpleViewer QGLViewer GLU ${QT_LIBRARIES})
#target_link_libraries(simpleViewer ${QGLViewer_LIBRARY} ${QT_LIBRARIES})


