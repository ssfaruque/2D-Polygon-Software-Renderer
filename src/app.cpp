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



void renderScene();
void showScreen();


App::App(const char* title, const int width, const int height,
            int* argc, char** argv):
m_running(true)
{
    Window::create(width, height, title, argc, argv);
    m_window = Window::getInstance();

    m_scene = new Scene("input/sample.txt");
}


App::~App()
{
    if(m_window)
        Window::destroy();

    if(m_scene)
    {
        m_scene->save("input/sample.txt");
        delete m_scene;
    }
}


void App::run()
{
    std::cout << "Loading scene..." << std::endl;
    glutDisplayFunc(renderScene);
    //glutIdleFunc(renderScene);
    glutMainLoop();
}


void renderScene()
{
    Window* window = Window::getInstance();
    window->clear();

    std::vector<Vertex> vertices;

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


    Entity* entity = new Polygon(vertices, 0xFFFFFFFF, true, true);

    entity->translate(Vector2f(0.3f, -0.3f));
    entity->scale(Vector2f(0.5f, 0.5f));
    entity->rotate(45.0);

    Scene scene;
    scene.load("input/sample.txt");
    scene.addEntity(entity);
    scene.displayEntities();
    scene.draw();
    scene.save("input/output_sameple.txt");

    // Matrix3f translationMatrix = createTranslationMatrix3f(Vector2f(0.0f, 0.1f));

    // Vector3f vertex(-0.4f, 0.0f, 1.0f);

    // Vector3f newPosition = translationMatrix * vertex;

    // std::cout << "(" << newPosition.x << ", " << newPosition.y << ", " << newPosition.z << ")" << std::endl;    

    // std::vector<Vertex> clippingWindow{};

    // Vertex clipV1(0.2, 0.7f);
    // Vertex clipV2(0.8f, 0.7f);
    // Vertex clipV3(0.8f, -0.2f);
    // Vertex clipV4(0.2f, -0.2f);

    // clippingWindow.push_back(clipV1);
    // clippingWindow.push_back(clipV2);
    // clippingWindow.push_back(clipV3);
    // clippingWindow.push_back(clipV4);

    // Entity* entity = new Polygon({}, 0xFFFFFFFF, true, true);
    // entity->addVertex(Vertex(0.0f, 0.0f));
    // entity->addVertex(Vertex(0.5f, 0.0f));
    // entity->addVertex(Vertex(0.5f, 0.5f));
    // entity->addVertex(Vertex(0.0f, 0.5f));
    // entity->draw(clippingWindow);


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