#ifdef __APPLE__
#include <GLUT/glut.h>
#endif
#ifdef __linux__
#include <GL/glut.h>
#endif

#include <iostream>

#include "app.h"
#include "window.h"
#include "frameBuffer.h"
#include "types.h"
#include "graphics.h"


void renderScene();
void showScreen();


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
    std::cout << "Loading scene..." << std::endl;

    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutMainLoop();
}


void renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT);

    Window* window = Window::getInstance();
    window->clear();

    bresenham(0.9f, -0.8f, -0.4f, -0.5f, 0xff0000ff);

    //dda(0.1f, 0.1f, 0.2f, -0.8f, 0xff0000ff);

    showScreen();
}


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