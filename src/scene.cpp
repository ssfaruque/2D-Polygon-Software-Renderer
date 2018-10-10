#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#include "scene.h"

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
        std::cout << "Opened file!" << std::endl;

        std::getline(inf, line);
        //int numPolygons = std::stoi(line);
        inf.ignore();

        while(!inf.eof())
        {
            while(std::getline(inf, line))
            {
                float x, y;
                iss << line;
                iss >> x >> y;
                iss.clear();

                std::cout << "x: " << x << " y: " << y << std::endl;
            }
        }
    }
}


void Scene::save(std::string saveFileName) const
{

}