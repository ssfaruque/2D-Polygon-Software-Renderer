#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#ifdef __linux__
#include <GL/glut.h>
#endif

#include <iostream>
#include <sstream>
#include <GL/gl.h>


#include "cli.h"
#include "window.h"
#include "scene.h"
#include "entity.h"
#include "primitive.h"
#include "frameBuffer.h"


Cli::Cli(Scene* scene):
m_scene(scene)
{}


std::vector<std::string> Cli::getTokensFromLine(const std::string& line) const
{
    std::vector<std::string> tokens{};

    std::istringstream iss(line);
    std::string token;

    while(std::getline(iss, token, ' '))
        tokens.push_back(token);

    return tokens;
}

void Cli::processInput()
{
    std::string inputLine;
    std::cout << ">> ";
    std::getline(std::cin, inputLine);

    std::vector<std::string> tokens = getTokensFromLine(inputLine);

    std::string command = !tokens.empty() ? tokens[0] : "";
    std::stringstream ss;

    if(command == "load" && tokens.size() == 2)
        cmdLoad(tokens[1]);    

    else if(command == "save" && tokens.size() == 2)
        cmdSave(tokens[1]); 

    else if(command == "setLineDrawingMode" && tokens.size() == 3)
        cmdSetLineDrawingMode(std::stoi(tokens[1]), std::stoi(tokens[2]));

    else if(command == "setClippingWindow" && tokens.size() == 5)
        cmdSetClippingWindow(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]), std::stof(tokens[4]));

    else if(command == "rasterize" && tokens.size() == 3)
    {
        Color color(0xFFFFFFFF);
        ss << std::hex << tokens[2];
        ss >> color.color;
        cmdRasterize(std::stoi(tokens[1]), color);
    }
    
    else if(command == "wireFrame" && tokens.size() == 3)
    {
        Color color(0xFFFFFFFF);
        ss << std::hex << tokens[2];
        ss >> color.color;
        cmdWireFrame(std::stoi(tokens[1]), color);
    }

    else if(command == "dda" && tokens.size() == 6)
    {
        Color color(0xFFFFFFFF);
        ss << std::hex << tokens[5];
        ss >> color.color;
        cmdDDA(stof(tokens[1]), stof(tokens[2]), stof(tokens[3]), stof(tokens[4]), color);
    }

    else if(command == "bresenham" && tokens.size() == 6)
    {
        Color color(0xFFFFFFFF);
        ss << std::hex << tokens[5];
        ss >> color.color;
        cmdBresenham(stof(tokens[1]), stof(tokens[2]), stof(tokens[3]), stof(tokens[4]), color);
    }

    else if(command == "polygon" && tokens.size() >= 7)
    {
        int numVertices = std::stoi(tokens[1]);
        std::vector<Vertex> vertices{};

        for(int i = 0; i < numVertices * 2; i += 2)
            vertices.push_back(Vertex(std::stof(tokens[i + 2]), std::stof(tokens[i + 3])));

        Color color(0xFFFFFFFF);
        ss << std::hex << tokens[2 + numVertices * 2];
        ss >> color.color;

        bool drawWithBresenham = bool(std::stoi(tokens[3 + numVertices * 2]));
        bool rasterized = bool(std::stoi(tokens[4 + numVertices * 2]));

        cmdPolygon(vertices, color, drawWithBresenham, rasterized);
    }

    else if(command == "translate" && tokens.size() == 4)
        cmdTranslate(std::stoi(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));

    else if(command == "scale" && tokens.size() == 4)
        cmdScale(std::stoi(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));

    else if(command == "rotate" && tokens.size() == 3)
        cmdRotate(std::stoi(tokens[1]), std::stof(tokens[2]));

    else if(command == "remove" && tokens.size() == 2)
        cmdRemove(std::stoi(tokens[1]));

    else if(command == "help" && tokens.size() == 1)
        cmdHelp();

    else if(command == "displayContents" && tokens.size() == 1)
        cmdDisplayEntities();

    else if(command == "setViewport" && tokens.size() == 5)
        cmdSetViewport(std::stof(tokens[1]), std::stof(tokens[2]), std::stoi(tokens[3]), std::stoi(tokens[4]));
    
    else if(command == "exit")
        exit(0);

    else if(tokens.size() > 0)
        std::cout << "Invalid command: " << inputLine << std::endl;
}


void Cli::cmdLoad(const std::string fileName)
{
    m_scene->load(fileName);
}


void Cli::cmdSave(const std::string fileName)
{
    m_scene->save(fileName);
}


void Cli::cmdSetLineDrawingMode(int id, int drawWithBresenham)
{
    for(Entity* entity : m_scene->m_entities)
    {
        if(id == -1)
            entity->setDrawWithBresenhamStatus(bool(drawWithBresenham));

        else if(entity->getId() == uint(id))
        {
            entity->setDrawWithBresenhamStatus(bool(drawWithBresenham));
            break;
        }
    }
}


void Cli::cmdSetClippingWindow(float xmin, float xmax, float ymin, float ymax)
{
    m_scene->setClippingWindow(xmin, xmax, ymin, ymax);
}


void Cli::cmdRasterize(int id, const Color color)
{
    for(Entity* entity : m_scene->m_entities)
    {
        if(entity->getId() == uint(id))
        {
            Polygon* polygon = dynamic_cast<Polygon*>(entity);
            if(polygon)
            {
                polygon->setRasterizationStatus(true);
                polygon->setColor(color);
            }

            break;
        }
    }
}


void Cli::cmdWireFrame(int id, const Color color)
{
    for (Entity *entity : m_scene->m_entities)
    {
        if (entity->getId() == uint(id))
        {
            Polygon *polygon = dynamic_cast<Polygon *>(entity);
            if (polygon)
            {
                polygon->setRasterizationStatus(false);
                polygon->setColor(color);
            }

            break;
        }
    }
}


void Cli::cmdDDA(float x1, float y1, float x2, float y2, Color color)
{
    Entity* entity = new Line(Vertex(x1, y1), Vertex(x2, y2), color, false);
    m_scene->addEntity(entity);
}


void Cli::cmdBresenham(float x1, float y1, float x2, float y2, Color color)
{
    Entity* entity = new Line(Vertex(x1, y1), Vertex(x2, y2), color, true);
    m_scene->addEntity(entity);
}


void Cli::cmdPolygon(const std::vector<Vertex>& vertices, Color color, bool drawWithBresenham, bool rasterize)
{
    Entity* entity = new Polygon(vertices, color, drawWithBresenham, rasterize);
    m_scene->addEntity(entity);
}


void Cli::cmdTranslate(int id, float xTrans, float yTrans)
{
    for (Entity *entity : m_scene->m_entities)
    {
        if (entity->getId() == uint(id))
        {
            entity->translate(Vector2f(xTrans, yTrans));
            break;
        }
    }
}


void Cli::cmdScale(int id, float xScale, float yScale)
{
    for (Entity *entity : m_scene->m_entities)
    {
        if (entity->getId() == uint(id))
        {
            entity->scale(Vector2f(xScale, yScale));
            break;
        }
    }
}


void Cli::cmdRotate(int id, float angle)
{
    for (Entity *entity : m_scene->m_entities)
    {
        if (entity->getId() == uint(id))
        {
            entity->rotate(angle);
            break;
        }
    }
}


void Cli::cmdRemove(int id)
{
    m_scene->removeEntity(id);
}


void Cli::cmdDisplayEntities() const
{
    m_scene->displayEntities();
}


void screenToNormalCoords(float* x, float* y)
{
    Window *window = Window::getInstance();
    *x = ((2.0f / window->getWidth())  * (*x)) - 1;
    *y = ((2.0f / window->getHeight()) * (*y)) - 1;
}


void Cli::cmdSetViewport(float x, float y, int width, int height) const
{
    screenToNormalCoords(&x, &y);
    glRasterPos2f(x, y);
    Window::getInstance()->resizeFrameBuffer(width, height);
}



void Cli::cmdHelp() const
{
    std::cout << "---------- LIST OF COMMANDS ----------" << std::endl;

    std::cout << "load: 'load fileName'" << std::endl;
    std::cout << "save: 'save fileName'" << std::endl;
    std::cout << "setLineDrawingMode: 'setLineDrawingMode id drawWithBresenham'" << std::endl;
    std::cout << "setClippingWindow: 'setClippingWindow xmin xmax ymin ymax'" << std::endl;
    std::cout << "rasterize: 'rasterize id color'" << std::endl;
    std::cout << "wireFrame: 'wireFrame id color'" << std::endl;
    std::cout << "dda: 'dda x1 y1 x2 y2 color'" << std::endl;
    std::cout << "bresenham: 'bresenham x1 y1 x2 y2 color'" << std::endl;
    std::cout << "polygon: 'polygon numVertices vertices... color drawWithBresenham rasterize'" << std::endl;
    std::cout << "translate: 'translate id xTrans yTrans'" << std::endl;
    std::cout << "scale: 'scale id xScale yScale'" << std::endl;
    std::cout << "rotate: 'rotate id angle'" << std::endl;
    std::cout << "remove: 'remove id'" << std::endl;
    std::cout << "displayContents: 'displayContents'" << std::endl;
    std::cout << "setViewport: 'setViewport x y width height'" << std::endl;
    std::cout << "exit: 'exit'" << std::endl;

    std::cout << "--------------------------------------" << std::endl;
}
