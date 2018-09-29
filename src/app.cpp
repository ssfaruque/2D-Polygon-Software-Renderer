#include <GL/freeglut.h>

#include "app.h"
#include "window.h"
#include "intTypes.h"


App::App(const char* title, const int width, const int height,
            int* argc, char** argv):
m_running(true)
{
    m_window = new Window(width, height, title, argc, argv);
}


App::~App()
{
    if(m_window)
        delete m_window;
}


void App::run()
{
    glutMainLoop();
}