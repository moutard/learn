
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


# === Project Sources ===
set (HEADERS
  vec3d.h
  edge.h
  mesh.h
  material.h
  bounding_box.h
  object3d.h
  light.h
  scene.h
  triangle.h
  vertex.h
)

set (SOURCES
  mesh.cpp
  material.cpp
  bounding_box.cpp
  object3d.cpp
  light.cpp
  scene.cpp
  triangle.cpp
  vertex.cpp
)

# preprocess all Qt files
QT4_WRAP_CPP(HEADERS_MOC ${HEADERS})

# Create executable called raytracer, that use the modified source.
#add_library(
#  hellogl_core SHARED
#  ${SOURCES}
#  ${HEADERS_MOC}
#  )

# link the executable you just created with all the external libraries
# pthread is required by GTest
#target_link_libraries(hellogl_core ${QT_LIBRARIES} ${OPENGL_LIBRARIES})

set(CMAKE_BUILD_TYPE Debug)

