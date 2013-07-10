cmake_minimum_required (VERSION 2.6)
project (Raytracer)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

FIND_PACKAGE(Qt4 COMPONENTS QtCore QtXml QtOpenGL QtGui REQUIRED)
set(QT_USE_QTXML 1)
set(QT_USE_QTOPENGL 1)

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
find_package(GLUT REQUIRED)
#include_directories(${QGLViewer_INCLUDE_DIRS})

set( RAYTRACER_SOURCES
  GLViewer.cpp
  QTUtils.cpp
  Vertex.cpp
  Triangle.cpp
  Mesh.cpp
  BoundingBox.cpp
  Material.cpp
  Object.cpp
  Light.cpp
  Scene.cpp
  RayTracer.cpp
  Ray.cpp
  Window.cpp
  Main.cpp
  )
set( RAYTRACER_HEADERS
  GLViewer.h
  QTUtils.h
  Vertex.h
  Triangle.h
  Mesh.h
  BoundingBox.h
  Material.h
  Object.h
  Light.h
  Scene.h
  RayTracer.h
  Ray.h
  Window.h
  Vec3D.h

  )
# Assure that all qt are correctly imported.
QT4_WRAP_CPP(RAYTRACER_HEADERS_MOC ${RAYTRACER_HEADERS})
# Create executable called simpleViewer
add_executable(
  raytracer
  ${RAYTRACER_SOURCES}
  ${RAYTRACER_HEADERS_MOC}
  )

# Add target link library
target_link_libraries(raytracer QGLViewer GLU GL ${QT_LIBRARIES} ${GTEST_LIBRARIES} pthread)

# you can add a specific executable for test.
# Use a variables for header and footers.

