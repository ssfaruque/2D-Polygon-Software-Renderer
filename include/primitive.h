#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <vector>

#include "entity.h"

class Line : public Entity
{
    private:
        Vertex m_v1;
        Vertex m_v2;
        bool m_drawWithBresenham;   // if false, draws with dda instead

    public:
        Line(const Vertex& v1, const Vertex& v2, Color color = Color(0xFFFFFFFF), bool drawWithBresenham = false):
        m_v1(v1), m_v2(v2), m_drawWithBresenham(drawWithBresenham)
        {
            m_color = color;
            m_id = 0;
        }

        void draw() override;

};


class Polygon : public Entity
{
    private:
        std::vector<Vertex> m_vertices;
        bool m_drawWithBresenham; // if false, draws with dda instead
        bool m_rasterized;  // if true, polygon will be filled

    public:
        Polygon(const std::vector<Vertex>& vertices, Color color = Color(0xFFFFFFFF), bool drawWithBresenham = false, bool rasterized = false):
        m_vertices(vertices), m_drawWithBresenham(drawWithBresenham), m_rasterized(rasterized)
        {
            m_color = color;
            m_id = 0;
        }
        
        void draw() override;
        inline uint getNumSides() const {return uint(m_vertices.size() - 1);}
};







#endif  // PRIMITIVE_H