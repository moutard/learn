# external libraries
#===================

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

# GTest
#------

# According the the FAQ of gtest it's better to recompile each time than
# installing.
#https://code.google.com/p/googletest/wiki/FAQ#Why_is_it_not_recommended_to_install_a_pre-compiled_copy_of_Goog

#find_package(GTEST REQUIRED)
#include_directories (${GTEST_INCLUDE_DIRS})

ADD_SUBDIRECTORY (gtest-1.7.0)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Source
# ============

# Source you want to test.
#-------------------------
include_directories (${hellogl_SOURCE_DIR}/src)

file(GLOB SOURCES
    ${hellogl_SOURCE_DIR}/src/*.cpp
    ${hellogl_SOURCE_DIR}/src/core/*.cpp
    ${hellogl_SOURCE_DIR}/src/utils/*.cpp
    ${hellogl_SOURCE_DIR}/src/widgets/*.cpp
  )
file(GLOB HEADERS
    ${hellogl_SOURCE_DIR}/src/*.h
    ${hellogl_SOURCE_DIR}/src/core/*.h
    ${hellogl_SOURCE_DIR}/src/utils/*.h
    ${hellogl_SOURCE_DIR}/src/widgets/*.h
  )

# Create a List given a variable.
set(SOURCES_WITHOUT_MAIN ${SOURCES})
message("${SOURCES}")
# Remove the main.cpp to only launch the tests.
list(REMOVE_ITEM SOURCES_WITHOUT_MAIN ${hellogl_SOURCE_DIR}/src/main.cpp)

# preprocess all Qt files
QT4_WRAP_CPP(HEADERS_MOC ${HEADERS})


# link the executable you just created with all the external libraries
# pthread is required by GTest
target_link_libraries(hellogl )

# Source that contains the test.
#-------------------------------
file(GLOB TESTS_SRC
  "*.cpp"
)
file(GLOB TESTS_INC
  "*.h"
)

add_executable(
  tests
  ${SOURCES_WITHOUT_MAIN}
  ${HEADERS_MOC}
  ${TESTS_INC}
  ${TESTS_SRC}
)

# Configuration de l'édition de lien.
target_link_libraries(tests ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${GTEST_LIBS} ${GTEST_LIBRARIES} gtest gtest_main pthread)
# Link test executable against gtest & gtest_main
#target_link_libraries(runUnitTests gtest gtest_main)
#add_test( runUnitTests runUnitTests )

# Preserve the old value if an exterior file already provide some.
# Do not add debug flag -g manually use CMAKE_BUILD_TYPE or -DCMAKE_BUILD_TYPE
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")

#add_definitions(-DGTEST_USE_OWN_TR1_TUPLE=1)
#set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -stdlib=libc++")
# Data files (contains model) needs to copy them in the

set(CMAKE_BUILD_TYPE Debug)
