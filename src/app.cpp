#include <GL/freeglut.h>

#include "app.h"
#include "window.h"
#include "types.h"
#include "graphics.h"

App::App(const char* title, const int width, const int height,
            int* argc, char** argv):
m_running(true)
{
    Window::create(width, height, title, argc, argv);
    m_window = Window::getInstance();
}


App::~App()
{
    if(m_window)
        Window::destroy();
}


void App::run()
{
    glutMainLoop();
}