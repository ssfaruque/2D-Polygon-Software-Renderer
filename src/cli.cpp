#include <iostream>
#include <sstream>

#include "cli.h"
#include "scene.h"
#include "entity.h"
#include "primitive.h"

Cli::Cli(Scene* scene):
m_scene(scene)
{}


void Cli::run()
{
    while(true)
    {
        processInput();
    }
}



std::string commands[] = {"load",
                          "save",
                          "setLineDrawingMode", 
                          "setClippingWindow",
                          "rasterize",
                          "dda",
                          "bresenham",
                          "polygon",
                          "translate",
                          "scale",
                          "rotate"};



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
        std::vector<Vertex> vertices(numVertices);

        for(int i = 0; i < numVertices; ++i)
            vertices.push_back(Vertex(std::stof(tokens[i + 2]), std::stof(tokens[i + 3])));

        Color color(0xFFFFFFFF);
        ss << std::hex << tokens[2 + numVertices];
        ss >> color.color;

        bool drawWithBresenham = bool(std::stoi(tokens[3 + numVertices]));
        bool rasterized = bool(std::stoi(tokens[4 + numVertices]));

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

    else if(command == "exit")
        exit(0);
    
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


void Cli::cmdPolygon(const std::vector<Vertex>& vertices, Color color, bool drawWithBresenham, bool rasterized)
{
    Entity* entity = new Polygon(vertices, color, drawWithBresenham, rasterized);
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
