#include <GL/freeglut.h>

#include "window.h"
#include "frameBuffer.h"


void callbackfunc()
{
    glClear(GL_COLOR_BUFFER_BIT);

    //glLoadIdentity();


    /*glPointSize(1.0f);

    glBegin(GL_POINTS);
    glColor4f(0.8f, 0.8f, 0.8f, 1.0f);

    
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f , -0.5f);
    

    glEnd();*/


    glutSwapBuffers();
}




Window::Window(uint width, uint height, std::string title, int* argc, char** argv):
m_width(width), m_height(height), m_title(title)
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); 
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(title.c_str());
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glutDisplayFunc(callbackfunc);
    glViewport(0, 0, width, height);

    m_frameBuffer = new FrameBuffer(width, height);
}


Window::~Window()
{
    if(m_frameBuffer)
        delete m_frameBuffer;
}