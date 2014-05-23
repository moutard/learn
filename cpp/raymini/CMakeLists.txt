cmake_minimum_required (VERSION 2.6)
project (Raytracer)

# === External libraries ===

# == GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# == Qt4
find_package(Qt4 REQUIRED)
# Components QtCore and QtGui are inserted by default.
# if you need another component you have to activate it, like this:
set(QT_USE_QTXML 1)
set(QT_USE_QTOPENGL 1)
include_directories(${QT_INCLUDE_DIRS})

# Qt need a bit more work.
# include is used to include a cmale module (or macro, here QT4_WRAPP_CPP)
include(${QT_USE_FILE})
# add preprocessors variables used by Qt (like QT_VERSION)
add_definitions(${QT_DEFINITIONS})
# learn more about qt and cmake at https://qt-project.org/quarterly/view/using_cmake_to_build_qt_projects

# == GLut
# I think it's optional (FindGLU and FindGLUT are available by default)
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})

# == QGLViewer
# as QGLViewer is an external library that CMake doesn't support by default.
# Indeed there is no module for it so we need to create the module by ourselves.
# - create a folder called cmake/Modules in our source directory root.
# - add a FindQGLViewer.cmake
#    I found a version here https://raw.github.com/RainerKuemmerle/g2o/master/cmake_modules/FindQGLViewer.cmake
# - tell cmake where to find this file
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
# after that you can use find_package to locate your library.
find_package(QGLViewer REQUIRED)
#include_directories(${QGLViewer_INCLUDE_DIRS})

# === Project Sources ===
set( SOURCES
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
set( HEADERS
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

# preprocess all Qt files
QT4_WRAP_CPP(HEADERS_MOC ${HEADERS})

# Create executable called raytracer, that use the modified source.
add_executable(
  raytracer
  ${SOURCES}
  ${HEADERS_MOC}
  )

# link the executable you just created with all the external libraries
# pthread is required by GTest
target_link_libraries(raytracer GL ${GLUT_LIBRARIES} ${QGLVIEWER_LIBRARY} ${QT_LIBRARIES} ${GTEST_LIBRARIES} pthread)

# you can add a specific executable for test.
# Data files (contains model) needs to copy them in the
file(COPY models DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

