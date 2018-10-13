#include <iostream>
#include <sstream>

#include "cli.h"
#include "scene.h"
#include "entity.h"


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
    std::getline(std::cin, inputLine);

    std::vector<std::string> tokens = getTokensFromLine(inputLine);

    std::string command = !tokens.empty() ? tokens[0] : "";

    if(command == "load" && tokens.size() >= 2)
        cmdLoad(tokens[1]);    

    else if(command == "save" && tokens.size() >= 2)
        cmdSave(tokens[1]); 

    else if(command == "setLineDrawingMode" && tokens.size() >= 3)
         cmdSetLineDrawingMode(std::stoi(tokens[1]), std::stoi(tokens[2]));
    
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
