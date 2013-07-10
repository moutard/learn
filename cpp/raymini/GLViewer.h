// *********************************************************
// OpenGL Viewer Class, based on LibQGLViewer, compatible
// with most hardware (OpenGL 1.2).
// Author : Tamy Boubekeur (boubek@gmail.com).
// Copyright (C) 2010 Tamy Boubekeur.
// All rights reserved.
// *********************************************************

#ifndef GLVIEWER_H
#define GLVIEWER_H

#include <QGLViewer/qglviewer.h>
#include <vector>
#include <string>

#include "Scene.h"

class GLViewer : public QGLViewer  {
public:
    
    typedef enum {Flat=0, Smooth=1} RenderingMode;
    
    GLViewer ();
    virtual ~GLViewer ();
    
    inline bool isWireframe () const { return wireframe; }
    inline int getRenderingMode () const { return renderingMode; }
    
    class Exception  {
        public:
            Exception (const std::string & msg) : message ("[GLViewer]"+msg) {}
            virtual ~Exception () {}
            const std::string & getMessage () const { return message; }
        private:
            std::string message;
        };

protected :
    void init();
    void draw ();
    QString helpString() const;
private:
    bool wireframe;
    RenderingMode renderingMode; 
};

#endif // GLVIEWER_H

// Some Emacs-Hints -- please don't remove:
//
//  Local Variables:
//  mode:C++
//  tab-width:4
//  End: