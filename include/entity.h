#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <vector>

#include "types.h"
#include "math.h"

static uint nextIDNum = 0;

class Entity
{
    protected:
        uint m_id;
        Color m_color;
        bool m_drawWithBresenham; // if false, draws with dda instead
        std::vector<Vertex> m_vertices;

    protected:
        Vertex calcCentroid() const;


    public:
        virtual void draw(const std::vector<Vertex>& clippingWindow) = 0;
        virtual void printDescription() const = 0;
        void setColor(Color color)
        {m_color = color;}

        Entity():
        m_id(nextIDNum++), m_color(0xFFFFFFFF), m_drawWithBresenham(false), m_vertices({})
        {}

        virtual ~Entity() = default;

        inline uint getId() const {return m_id;}
        inline void addVertex(const Vertex& vertex) {m_vertices.push_back(vertex);};
        inline uint getNumVertices() const {return uint(m_vertices.size());}
        inline void setDrawWithBresenhamStatus(bool drawWithBresenham) {m_drawWithBresenham = drawWithBresenham;}

        
        void translate(const Vector2f& vector);
        void scale(const Vector2f& vector);
        void rotate(float angle);



        friend class Scene;
};






#endif