#include <GL/freeglut.h>
#include <cstring>

#include "window.h"
#include "frameBuffer.h"


Window* Window::m_window = nullptr;


void callbackfunc()
{ 
    glClear(GL_COLOR_BUFFER_BIT);

    /*glPointSize(1.0f);

    glBegin(GL_POINTS);
    glColor4f(0.8f, 0.8f, 0.8f, 1.0f);

    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f , -0.5f);
    

    glEnd();*/

    Window* window = Window::getInstance();

    uint width = window->getWidth();
    uint height = window->getHeight();

    memset(window->getFrameBuffer()->getBuffer(), 0, sizeof(u32) * window->getWidth() * window->getHeight());

    for(uint i = height / 2; i < height; ++i)
    {
        window->getFrameBuffer()->setPixel(i, width / 2 + i - height/2, 0xFFFFFFFF);
    }


    glDrawPixels(window->getWidth(),
                 window->getHeight(),
                 GL_RGBA,
                 GL_UNSIGNED_INT_8_8_8_8,
                 window->getFrameBuffer()->getBuffer());



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
    glViewport(0, 0, width, height);

    m_frameBuffer = new FrameBuffer(width, height);


    glutDisplayFunc(callbackfunc);
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