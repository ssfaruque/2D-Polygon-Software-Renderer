#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <vector>

#include "types.h"


static uint nextIDNum = 0;

class Entity
{
    protected:
        uint m_id;
        Color m_color;
        std::vector<Vertex> m_vertices;

    public:
        virtual void draw() = 0;
        virtual void printDescription() const = 0;
        void setColor(Color color)
        {m_color = color;}

        Entity():
        m_id(nextIDNum++), m_color(0xFFFFFFFF), m_vertices({})
        {}

        inline uint getId() const {return m_id;}
        inline void addVertex(const Vertex& vertex) {m_vertices.push_back(vertex);};
        inline uint getNumVertices() const {return uint(m_vertices.size());}

        friend class Scene;
};






#endif