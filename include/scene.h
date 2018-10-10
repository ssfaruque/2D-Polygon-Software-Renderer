#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "entity.h"

class Scene
{
    private:
        std::vector<Entity*> m_entities;

    public:
        Scene();
        ~Scene();

        void addEntity(Entity* entity);
        void draw();
        void displayEntities() const;

        

};





#endif  // SCENE_H