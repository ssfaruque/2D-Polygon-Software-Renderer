#include <GL/freeglut.h>
#include <cstring>

#include "window.h"
#include "frameBuffer.h"

#include "graphics.h"


#include <iostream>

Window* Window::m_window = nullptr;


void showScreen()
{
    Window* window = Window::getInstance();

    glDrawPixels(window->getWidth(),
                 window->getHeight(),
                 GL_RGBA,
                 GL_UNSIGNED_INT_8_8_8_8,
                 window->getFrameBuffer()->getBuffer());
    glutSwapBuffers();
}

float x = 70, y = 70;

void callbackfunc()
{ 
    glClear(GL_COLOR_BUFFER_BIT);

    Window* window = Window::getInstance();
    window->clear();

    x+=1;;
    y+=1;;


    drawLine(x - 70, y - 70, x, y, 0x00FF00FF);

    showScreen();
}


Window::Window(uint width, uint height, std::string title, int* argc, char** argv):
m_width(width), m_height(height), m_title(title)
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); 
    glutInitWindowSize(width, height);
    glutInitWindowPosition(-1, -1);
    glutCreateWindow(title.c_str());
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glViewport(0, 0, width, height);

    m_frameBuffer = new FrameBuffer(width, height);

    glutDisplayFunc(callbackfunc);
    glutIdleFunc(callbackfunc);
}


Window::~Window()
{
    if(m_frameBuffer)
        delete m_frameBuffer;
}


void Window::create(uint width, uint height, std::string title, int* argc, char** argv)
{
    if(!Window::m_window)
        Window::m_window = new Window(width, height, title, argc, argv);
}


Window* Window::getInstance()
{
    if(Window::m_window)
        return Window::m_window;

    return nullptr;
}


void Window::destroy()
{
    if(Window::m_window)
    {
        delete Window::m_window;
        Window::m_window = nullptr;
    }
}


void Window::clear(Color color)
{
    m_frameBuffer->clear(color);
}