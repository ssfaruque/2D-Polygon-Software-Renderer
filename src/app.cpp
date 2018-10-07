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

    std::vector<Vertex> vertices;

    Vertex v1(0.0f, 0.2f);
    Vertex v2(0.5f, 0.5f);
    Vertex v3(0.5f, -0.5f);
    Vertex v4(0.0f, -0.2f);
    Vertex v5(-0.5f, -0.5f);
    Vertex v6(-0.5f, 0.5f);

    bresenham(v1.x, v1.y, v2.x, v2.y, 0xff0000ff);
    bresenham(v2.x, v2.y, v3.x, v3.y, 0xff0000ff);
    bresenham(v3.x, v3.y, v4.x, v4.y, 0xff0000ff);
    bresenham(v4.x, v4.y, v5.x, v5.y, 0xff0000ff);
    bresenham(v5.x, v5.y, v6.x, v6.y, 0xff0000ff);
    bresenham(v6.x, v6.y, v1.x, v1.y, 0xff0000ff);

    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    vertices.push_back(v4);
    vertices.push_back(v5);
    vertices.push_back(v6);



    // TRIANGLE

    // Vertex v1(-0.5f, 0.3f);
    // Vertex v2(0.5f, 0.5f);
    // Vertex v3(0.5f, -0.4f);

    // bresenham(v1.x, v1.y, v2.x, v2.y, 0xff0000ff);
    // bresenham(v2.x, v2.y, v3.x, v3.y, 0xff0000ff);
    // bresenham(v3.x, v3.y, v1.x, v1.y, 0xff0000ff);

    // vertices.push_back(v1);
    // vertices.push_back(v2);
    // vertices.push_back(v3);


    for(auto& v : vertices) {normalToScreenCoords(&v.x, &v.y);}


    polygonFill(vertices, 0xFF0000FF);

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