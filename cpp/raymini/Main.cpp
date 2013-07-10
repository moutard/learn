#include <string>
#include <iostream>

#include <gtest/gtest.h>

#include <QApplication>

#include "Window.h"

using namespace std;

int main (int argc, char **argv) {

  //testing::InitGoogleTest(&argc, argv);
  //RUN_ALL_TESTS();

  QApplication raymini (argc, argv);
  //setBoubekQTStyle (raymini);
  std::cout<<"QApplication ok"<<std::endl;
  //QApplication::setStyle (new QPlastiqueStyle);
  //GLViewer viewer;

    Window * window = new Window ();
#if QT_VERSION < 0x040000


  // Set the viewer as the application main widget.
  //application.setMainWidget(&viewer);
#else
  //viewer.setWindowTitle("simpleViewer");
#endif
    window->show();
  // Make the viewer window visible on screen.
  //viewer.show();

  // Run main loop.
  return raymini.exec();

}

