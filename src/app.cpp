#ifdef __APPLE__
#include <GLUT/glut.h>
#endif
#ifdef __linux__
#include <GL/glut.h>
#endif

#include <iostream>
#include <vector>

#include "app.h"
#include "window.h"
#include "frameBuffer.h"
#include "types.h"
#include "graphics.h"
#include "primitive.h"
#include "scene.h"
#include "math.h"
#include "cli.h"



App* App::m_app = nullptr;




void renderScene();
void showScreen();


App::App(const char* title, const int width, const int height,
            int* argc, char** argv):
m_running(true)
{
    Window::create(width, height, title, argc, argv);
    m_window = Window::getInstance();
    m_scene = new Scene("input/sample.txt");
    m_cli = new Cli(m_scene);
}


App::~App()
{
    if(m_window)
        Window::destroy();

    m_scene->save("input/output_sample.txt");

    if(m_scene)
        delete m_scene;

    if(m_cli)
        delete m_cli;
}


void App::create(const char* title, const int width, const int height,
                 int* argc, char** argv)
{
    if(!App::m_app)
        m_app = new App(title, width, height, argc, argv);
}


App* App::getInstance()
{
    if(App::m_app)
        return m_app;

    return nullptr;
}


void App::run()
{
    std::cout << "Loading scene..." << std::endl << std::endl;
    glutDisplayFunc(renderScene);
    //glutIdleFunc(renderScene);
    glutMainLoop();
}


void renderScene()
{
    Window* window = Window::getInstance();
    window->clear();

    App* app = App::getInstance();
    app->m_cli->processInput();
    app->m_scene->draw();

    showScreen();
    glutPostRedisplay();
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