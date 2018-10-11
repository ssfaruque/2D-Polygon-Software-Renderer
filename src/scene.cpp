#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#include "scene.h"
#include "primitive.h"


Scene::Scene():
m_entities({})
{
}


Scene::Scene(std::string loadFileName)
{
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
        entity->draw();
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
    std::ifstream inf(loadFileName);
    std::string line;
    std::stringstream iss;

    if(inf.is_open())
    {
        //std::cout << "Opened file!" << std::endl;
        std::getline(inf, line);
        std::getline(inf, line);
        
        while(!inf.eof())
        {
            std::getline(inf, line);
            uint numVertices = stoi(line);
            //std::cout << "numVertices: " << numVertices << std::endl;

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
                //std::cout << "x: " << x << " y: " << y << std::endl;
                if(inf.eof()) break;
            }

            addEntity(entity);
        }
    }

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