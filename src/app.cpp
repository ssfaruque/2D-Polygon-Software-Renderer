#include <GL/freeglut.h>
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


float x = 0, y  = 0;

void renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT);

    Window* window = Window::getInstance();
    window->clear();

    x+=1;;
    y+=1;;


    drawLine(x - 70, y - 70, x, y, 0x00FF00FF);

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