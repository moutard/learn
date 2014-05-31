
# === External libraries ===

# == Qt4
find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL REQUIRED)
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

# == OpenGL
# I think it's optional (FindGLU and FindGLUT are available by default)
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})


# == GLut
# I think it's optional (FindGLU and FindGLUT are available by default)
#find_package(GLUT REQUIRED)
#include_directories(${GLUT_INCLUDE_DIRS})

# == QGLViewer
# as QGLViewer is an external library that CMake doesn't support by default.
# Indeed there is no module for it so we need to create the module by ourselves.
# - create a folder called cmake/Modules in our source directory root.
# - add a FindQGLViewer.cmake
#    I found a version here https://raw.github.com/RainerKuemmerle/g2o/master/cmake_modules/FindQGLViewer.cmake
# - tell cmake where to find this file
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
# after that you can use find_package to locate your library.
#find_package(QGLViewer REQUIRED)
#include_directories(${QGLViewer_INCLUDE_DIRS})

# === Project Sources ===

set (HEADERS
  hgexception.h
  vec3d.h
  edge.h
  glwidget.h
  hglwidget.h
  qdessingl.h
  myglwidget.h
  mesh.h
  meshfactory.h
  qtlogo.h
  triangle.h
  vertex.h
  window.h
)

set (SOURCES
  hgexception.cpp
  glwidget.cpp
  hglwidget.cpp
  qdessingl.cpp
  myglwidget.cpp
  mesh.cpp
  meshfactory.cpp
  qtlogo.cpp
  triangle.cpp
  vertex.cpp
  window.cpp
)
# it's consdidered as a bad practice
#file(GLOB SOURCES
#    "*.cpp"
#  )
#file(GLOB HEADERS
#    "*.h"
#  )

# preprocess all Qt files
QT4_WRAP_CPP(HEADERS_MOC ${HEADERS})

# Create executable called raytracer, that use the modified source.
add_executable(
  hellogl
  main.cpp
  ${SOURCES}
  ${HEADERS_MOC}
  )

# link the executable you just created with all the external libraries
# pthread is required by GTest
target_link_libraries(hellogl ${QT_LIBRARIES} ${OPENGL_LIBRARIES})

# you can add a specific executable for test.
# Data files (contains model) needs to copy them in the
#file(COPY models DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

# To resolve confict names with GTEST
#SET(GTEST_USE_OWN_TR1_TUPLE 1)
#add_definitions(${GTEST_USE_OWN_TR1_TUPLE})

#CPPFLAGS=-DGTEST_USE_OWN_TR1_TUPLE=1
#add_definitions(-DGTEST_USE_OWN_TR1_TUPLE=1)
#set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -stdlib=libc++ -std=c++11")
# Data files (contains model) needs to copy them in the
set(CMAKE_BUILD_TYPE Debug)
