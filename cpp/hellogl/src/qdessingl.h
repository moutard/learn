#ifndef QDESSINGL_H
#define QDESSINGL_H

#include <qgl.h>

class QDessinGL : public QGLWidget
{
    Q_OBJECT

    private:
        GLfloat rtri, rquad;
        QTimer *m_timer;
    public:
        QDessinGL(int timerInterval=0, QWidget *parent=0);
    protected:
        void initializeGL();
        void resizeGL(int w,int h);
        void paintGL();
        void timeOut();

};
#endif // QDESSINGL_H
