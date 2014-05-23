This README is focused on linux distribution only for the moment.
mac version is comming soon.

== Prerequisites

  - Qt
  sudo aptitude qt-sdk libqt4-dev
  sudo aptitude install qt4-dev-tools libqt4-dev libqglviewer-qt4-2

   - libqglviewer
   sudo aptitude install libqglviewer-qt4-dev
   to get <QGLViewer/qglviewer.h>


  - GLUT
  sudo aptitude install freeglut3-dev
  Need to get the file <GL/glut.h>
  this file should be in /usr/include/GL

  (if you need more information http://www.libqglviewer.com/installUnix.html#linux)

== Get the code
git clone http:// .. SO

== Compilation

cmake
qglviewer
qt

-- Set CMAKE
The package FindQGLVIEWER.cmake is not installed by default with the cmake
distribution, that's why we created a specific FindQGLVIEWER.cmake file that is
in the cmake/Modules/ folder of our project. This file is automatically added
by our CMakeLists.txt


Issues
In file included from /usr/include/QGLViewer/manipulatedFrame.h:26:0,
                 from /usr/include/QGLViewer/manipulatedCameraFrame.h:26,
                 from /usr/include/QGLViewer/camera.h:26,
                 from /usr/include/QGLViewer/qglviewer.h:26,
                 from /home/rmoutard/learn/cpp/raymini/GLViewer.h:12,
                 from /home/rmoutard/learn/cpp/raymini/GLViewer.cpp:9:
/usr/include/QGLViewer/frame.h:30:22: fatal error: qobject.h: No such file or directory

if you check the code of
  /usr/include/QGLViewer/frame.h
you can see something like
#if QT_VERSION >= 0x040000
  # include <QObject>
  # include <QString>
#else
 # include <qobject.h>
 # include <qstring.h>
#endif

the problem seems to be that qobject doesn't exists, because the but QObject yes.
SO that's a problem with QT_VERSION.
