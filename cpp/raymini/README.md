This README is focused on linux distribution only for the moment.
mac version is comming soon.

== Prerequisites

  - CMake
  ```bash
  sudo aptitude install cmake
  ```

  - Qt
  sudo aptitude libqt4-dev (qt-sdk)
  ```bash
  sudo aptitude install libqt4-dev
  ```

   - libqglviewer
   ```bash
   sudo aptitude install libqglviewer-qt4-dev
   ```
   to get <QGLViewer/qglviewer.h>
   (if you need more information http://www.libqglviewer.com/installUnix.html#nux)

  - GLUT
  ```bash
  sudo aptitude install freeglut3-dev
  ```
  Need to get the file <GL/glut.h>
  this file should be in /usr/include/GL

== Get the code
  let's call <DIR_RAYMINI> the directory where you clone the code.
  git clone http:// <DIR_RAYMINI>

== Compilation

-- Set CMAKE
The package FindQGLVIEWER.cmake is not installed by default with the cmake
distribution, that's why we created a specific FindQGLVIEWER.cmake file that is
in the cmake/Modules/ folder of our project. This file is automatically added
by our CMakeLists.txt

  ```bash
  mkdir raymini-build
  cd raymini-build
  cmake <DIR_RAYMINI>
  make
  ```

=== Issues ===

This is not really issues you could find, it's more to help during the coding
process.

== qobject.h no such file
In file included from /usr/include/QGLViewer/manipulatedFrame.h:26:0,
                 from /usr/include/QGLViewer/manipulatedCameraFrame.h:26,
                 from /usr/include/QGLViewer/camera.h:26,
                 from /usr/include/QGLViewer/qglviewer.h:26,
                 from /home/rmoutard/learn/cpp/raymini/GLViewer.h:12,
                 from /home/rmoutard/learn/cpp/raymini/GLViewer.cpp:9:
/usr/include/QGLViewer/frame.h:30:22: fatal error: qobject.h: No such file or directory

It means that the the compiler can not find the qobject.h that should be
provided by qt4-dev

Solution:
 - check that this file are present
 /usr/include/qt4/Qt/qobject.h
 /usr/include/qt4/QtCore/qobject.h
 if not :
 - check that qt4-dev is installed.

if you check the code of
  /usr/include/QGLViewer/frame.h

Rq: QT_VERSION is defined by add_definitions(${QT_DEFINITIONS}) in CMakeLists.txt
#if QT_VERSION >= 0x040000
  # include <QObject>
  # include <QString>
#else
 # include <qobject.h>
 # include <qstring.h>
#endif

== GL/glut.h no such file
