#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <string>

#include "entity.h"

class Scene
{
    private:
        std::vector<Entity*> m_entities;

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

};



#endif  // SCENE_H