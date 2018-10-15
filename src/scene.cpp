#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "scene.h"
#include "primitive.h"



Scene::Scene():
m_entities({}),
 m_clippingWindow({}),
 m_clipXmin(-1.0f), m_clipXmax(1.0f), m_clipYmin(-1.0f), m_clipYmax(1.0f)
{
    m_clippingWindow.push_back(Vertex(m_clipXmin, m_clipYmax));
    m_clippingWindow.push_back(Vertex(m_clipXmax, m_clipYmax));
    m_clippingWindow.push_back(Vertex(m_clipXmax, m_clipYmin));
    m_clippingWindow.push_back(Vertex(m_clipXmin, m_clipYmin));
}


Scene::Scene(std::string loadFileName):
m_entities({}), m_clippingWindow({}),
 m_clipXmin(-1.0f), m_clipXmax(1.0f), m_clipYmin(-1.0f), m_clipYmax(1.0f)

{
    m_clippingWindow.push_back(Vertex(m_clipXmin, m_clipYmax));
    m_clippingWindow.push_back(Vertex(m_clipXmax, m_clipYmax));
    m_clippingWindow.push_back(Vertex(m_clipXmax, m_clipYmin));
    m_clippingWindow.push_back(Vertex(m_clipXmin, m_clipYmin));
    
    load(loadFileName);
}


Scene::~Scene()
{
    m_entities.clear();
}


void Scene::addEntity(Entity* entity)
{
    m_entities.push_back(entity);
}


void Scene::clean()
{
    m_entities.clear();
}


void Scene::draw()
{
    for(auto& entity : m_entities)
        entity->draw(m_clippingWindow);
}


void Scene::displayEntities() const
{
    std::cout << "*** SCENE CONTENTS ***" << std::endl;

    for(auto& entity : m_entities)
        entity->printDescription();

    std::cout << "*************************************************" << std::endl;
}


void Scene::load(std::string loadFileName)
{
    m_entities.clear();

    std::ifstream inf(loadFileName);
    std::string line;
    std::stringstream iss;

    if(inf.is_open())
    {
        std::getline(inf, line);
        std::getline(inf, line);
        
        while(!inf.eof())
        {
            std::getline(inf, line);
            uint numVertices = stoi(line);

            Entity* entity = nullptr;

            if(numVertices == 2)
                entity = new Line;
            
            else
                entity = new Polygon;

            while(true)
            {
                std::getline(inf, line);

                if(line.empty()) break;

                float x, y;
                iss << line;
                iss >> x >> y;
                iss.clear();

                Vertex vertex(x, y, 1);

                entity->addVertex(vertex);

                if(inf.eof()) break;
            }

            addEntity(entity);
        }
    }

    else
        std::cout << "Failed to open file: " << loadFileName << std::endl;

    inf.close();
}


void Scene::save(std::string saveFileName) const
{
    std::ofstream outf(saveFileName);
    std::string line;
    std::stringstream iss;

    outf << m_entities.size() << std::endl;

    for(auto& entity : m_entities)
    {
        outf << std::endl;

        outf << entity->getNumVertices() << std::endl;

        for(auto& vertex : entity->m_vertices)
            outf << vertex.x << " " << vertex.y << std::endl;
    }

    outf.close();
}


void Scene::setClippingWindow(float clipXmin, float clipXmax, float clipYmin, float clipYmax)
{
    m_clipXmin = clipXmin;  m_clipXmax = clipXmax;
    m_clipYmin = clipYmin;  m_clipYmax = clipYmax;

    Vertex v1(clipXmin, clipYmax);
    Vertex v2(clipXmax, clipYmax);
    Vertex v3(clipXmax, clipYmin);
    Vertex v4(clipXmin, clipYmin);

    m_clippingWindow.clear();

    m_clippingWindow.push_back(v1);
    m_clippingWindow.push_back(v2);
    m_clippingWindow.push_back(v3);
    m_clippingWindow.push_back(v4);
}


void Scene::removeEntity(uint id)
{
    auto newEnd = std::remove_if(m_entities.begin(),
                   m_entities.end(),
                   [id](Entity* entity){return entity->getId() == id;});
    m_entities.erase(newEnd, m_entities.end());
}
