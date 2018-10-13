#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <string>

#include "types.h"

class Entity;

class Scene
{
    private:
        std::vector<Entity*> m_entities;
        std::vector<Vertex> m_clippingWindow;
        float m_clipXmin;
        float m_clipXmax;
        float m_clipYmin;
        float m_clipYmax;


    public:
        Scene();
        Scene(std::string loadFileName);
        ~Scene();

        void addEntity(Entity* entity);
        void clean();
        void draw();
        void displayEntities() const;
        void load(std::string loadFileName);
        void save(std::string saveFileName) const;
        void setClippingWindow(float clipXmin, float clipXmax, float clipYmin, float clipYmax);

        friend class Cli;
};



#endif  // SCENE_H