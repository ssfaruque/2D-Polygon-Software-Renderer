#include <GL/freeglut.h>

#include "app.h"
#include "window.h"


#include <iostream>

void callbackfunc()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(2.0f);
    glBegin(GL_POINTS);
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f);

    for(int i = 0; i < 100; ++i)
    {
        glVertex2f(1080/2 + i,720/2 + i);
    }


    glEnd();
    glFlush();

    glutSwapBuffers();
}


App::App(const char* TITLE, const int WIDTH, const int HEIGHT,
            int* argc, char** argv):
m_running(true)
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); 
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(TITLE);
    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);

    glutDisplayFunc(callbackfunc);

    glutMainLoop();
}