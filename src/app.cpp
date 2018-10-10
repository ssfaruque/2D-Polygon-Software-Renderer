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
#include "math.h"


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

    // Vertex v1(0.0f, 0.2f);
    // Vertex v2(0.5f, 0.5f);
    // Vertex v3(0.5f, -0.5f);
    // Vertex v4(0.0f, -0.2f);
    // Vertex v5(-0.5f, -0.5f);
    // Vertex v6(-0.5f, 0.5f);

    // bresenham(v1.x, v1.y, v2.x, v2.y, 0xff0000ff);
    // bresenham(v2.x, v2.y, v3.x, v3.y, 0xff0000ff);
    // bresenham(v3.x, v3.y, v4.x, v4.y, 0xff0000ff);
    // bresenham(v4.x, v4.y, v5.x, v5.y, 0xff0000ff);
    // bresenham(v5.x, v5.y, v6.x, v6.y, 0xff0000ff);
    // bresenham(v6.x, v6.y, v1.x, v1.y, 0xff0000ff);

    // vertices.push_back(v1);
    // vertices.push_back(v2);
    // vertices.push_back(v3);
    // vertices.push_back(v4);
    // vertices.push_back(v5);
    // vertices.push_back(v6);



    // OTHER SHAPE

    // Vertex v1(0.2f, 0.2f);
    // Vertex v2(0.1f, 0.0f);
    // Vertex v3(0.2f, -0.2f);
    // Vertex v4(-0.2f, -0.2f);
    // Vertex v5(-0.1f, 0.0f);
    // Vertex v6(-0.2f, 0.2f);

    // bresenham(v1.x, v1.y, v2.x, v2.y, 0xff0000ff);
    // bresenham(v2.x, v2.y, v3.x, v3.y, 0xff0000ff);
    // bresenham(v3.x, v3.y, v4.x, v4.y, 0xff0000ff);
    // bresenham(v4.x, v4.y, v5.x, v5.y, 0xff0000ff);
    // bresenham(v5.x, v5.y, v6.x, v6.y, 0xff0000ff);
    // bresenham(v6.x, v6.y, v1.x, v1.y, 0xff0000ff);

    // vertices.push_back(v1);
    // vertices.push_back(v2);
    // vertices.push_back(v3);
    // vertices.push_back(v4);
    // vertices.push_back(v5);
    // vertices.push_back(v6);



    // TRIANGLE

    // Vertex v1(-0.2f, 0.4f);
    // Vertex v2(0.6f, -0.2f);
    // Vertex v3(-0.1f, -0.1f);
 
    // bresenham(v1.x, v1.y, v2.x, v2.y, 0xff0000ff);
    // bresenham(v2.x, v2.y, v3.x, v3.y, 0xff0000ff);
    // bresenham(v3.x, v3.y, v1.x, v1.y, 0xff0000ff);

    // vertices.push_back(v1);
    // vertices.push_back(v2);
    // vertices.push_back(v3);


    // SQUARE

    // Vertex v1(-0.5f, 0.5f);
    // Vertex v2(0.5f, 0.5f);
    // Vertex v3(0.5f, -0.5f);
    // Vertex v4(-0.5f, -0.5f);
 
    // bresenham(v1.x, v1.y, v2.x, v2.y, 0xff0000ff);
    // bresenham(v2.x, v2.y, v3.x, v3.y, 0xff0000ff);
    // bresenham(v3.x, v3.y, v4.x, v4.y, 0xff0000ff);
    // bresenham(v4.x, v4.y, v1.x, v1.y, 0xff0000ff);

    // vertices.push_back(v1);
    // vertices.push_back(v2);
    // vertices.push_back(v3);
    // vertices.push_back(v4);



    // EXTREME SHAPE

    Vertex v1(-0.15f, 0.35f);
    Vertex v2(0.0f, 0.35f);
    Vertex v3(0.2f, 0.0f);
    Vertex v4(0.0f, -0.25f);
    Vertex v5(-0.15f, -0.05f);
    Vertex v6(0.05f, -0.1);
    Vertex v7(-0.15f, 0.2f);
    Vertex v8(-0.5f, -0.3);
    Vertex v9(-0.3f, 0.4);

    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    vertices.push_back(v4);
    vertices.push_back(v5);
    vertices.push_back(v6);
    vertices.push_back(v7);
    vertices.push_back(v8);
    vertices.push_back(v9);

    bresenham(v1.x, v1.y, v2.x, v2.y, 0xffffffff);
    bresenham(v2.x, v2.y, v3.x, v3.y, 0xffffffff);
    bresenham(v3.x, v3.y, v4.x, v4.y, 0xffffffff);
    bresenham(v4.x, v4.y, v5.x, v5.y, 0xffffffff);
    bresenham(v5.x, v5.y, v6.x, v6.y, 0xffffffff);
    bresenham(v6.x, v6.y, v7.x, v7.y, 0xffffffff);
    bresenham(v7.x, v7.y, v8.x, v8.y, 0xffffffff);
    bresenham(v8.x, v8.y, v9.x, v9.y, 0xffffffff);
    bresenham(v9.x, v9.y, v1.x, v1.y, 0xffffffff);


 
    // Vertex v1(1.5f, 0.0f);
    // Vertex v2(0.0f, -1.6f);
    // Vertex v3(-1.4f, 0.2f);
    // Vertex v4(0.1f, 1.1f);

    // vertices.push_back(v1);
    // vertices.push_back(v2);
    // vertices.push_back(v3);
    // vertices.push_back(v4);

    // cohenSutherlandClipping(vertices, -1.0f, 1.0f, -1.0f, 1.0f, 0x00ff00ff, BRESENHAM);

    for(auto& v : vertices) {normalToScreenCoords(&v.x, &v.y);}

    polygonFill(vertices, 0x330000ff);

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