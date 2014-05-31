#include "QDessinGL.h"

QDessinGL::QDessinGL(int timerInterval, QWidget *parent):QGLWidget(parent)
{
    rtri=0.0f;
    rquad=0.0f;
}

void QDessinGL::initializeGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void QDessinGL::resizeGL(int width,int height)
{
    if (height==0)                                      // Prevent A Divide By Zero By
        {
                height=1;                                       // Making Height Equal One
        }

        glViewport(0,0,width,height);                       // Reset The Current Viewport

        glMatrixMode(GL_PROJECTION);                        // Select The Projection Matrix
        glLoadIdentity();                                   // Reset The Projection Matrix

        // Calculate The Aspect Ratio Of The Window
        //gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

        glMatrixMode(GL_MODELVIEW);                         // Select The Modelview Matrix
        glLoadIdentity();
}

void QDessinGL::paintGL()
{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
        glLoadIdentity();                                   // Reset The Current Modelview Matrix
        glTranslatef(-1.5f,0.0f,-6.0f);                     // Move Left 1.5 Units And Into The Screen 6.0
        glRotatef(rtri,0.0f,1.0f,0.0f);
        // Rotate The Triangle On The Y axis ( NEW )
        glBegin(GL_TRIANGLES);                              // Start Drawing A Triangle
                glColor3f(1.0f,0.0f,0.0f);                      // Set Top Point Of Triangle To Red
                glVertex3f( 0.0f, 1.0f, 0.0f);                  // First Point Of The Triangle
                glColor3f(0.0f,1.0f,0.0f);                      // Set Left Point Of Triangle To Green
                glVertex3f(-1.0f,-1.0f, 0.0f);                  // Second Point Of The Triangle
                glColor3f(0.0f,0.0f,1.0f);                      // Set Right Point Of Triangle To Blue
                glVertex3f( 1.0f,-1.0f, 0.0f);                  // Third Point Of The Triangle
        glEnd();                                            // Done Drawing The Triangle


        glLoadIdentity();                                   // Reset The Current Modelview Matrix
        glTranslatef(1.5f,0.0f,-6.0f);                      // Move Right 1.5 Units And Into The Screen 6.0
        glRotatef(rquad,1.0f,0.0f,0.0f);                    // Rotate The Quad On The X axis ( NEW )
        glColor3f(0.5f,0.5f,1.0f);                          // Set The Color To Blue One Time Only
        glBegin(GL_QUADS);                                  // Draw A Quad
                glVertex3f(-1.0f, 1.0f, 0.0f);                  // Top Left
                glVertex3f( 1.0f, 1.0f, 0.0f);                  // Top Right
                glVertex3f( 1.0f,-1.0f, 0.0f);                  // Bottom Right
                glVertex3f(-1.0f,-1.0f, 0.0f);                  // Bottom Left
        glEnd();                                            // Done Drawing The Quad

}

void QDessinGL::timeOut()
{
    rtri += 0.5f;
    rquad -= 0.25f;
    updateGL();
}
