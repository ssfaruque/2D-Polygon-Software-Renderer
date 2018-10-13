#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <iostream>
#include <vector>

#include "entity.h"

class Line : public Entity
{
    private:

    public:
        Line(const Vertex& v1, const Vertex& v2, Color color = Color(0xFFFFFFFF), bool drawWithBresenham = false)

        {
            m_drawWithBresenham = drawWithBresenham;
            m_vertices.push_back(v1);
            m_vertices.push_back(v2);
            m_color = color;
        }

        Line()
        {}

        void draw(const std::vector<Vertex>& clippingWindow) override;

        void printDescription() const override;

};


class Polygon : public Entity
{
    private:
        bool m_rasterized;  // if true, polygon will be filled

    public:
        Polygon(const std::vector<Vertex>& vertices, Color color = Color(0xFFFFFFFF), bool drawWithBresenham = false, bool rasterized = false):
        m_rasterized(rasterized)
        {
            m_drawWithBresenham = drawWithBresenham;
            m_vertices = vertices;
            m_color = color;
        }

        Polygon():
        m_rasterized(false)
        {}
        
        void draw(const std::vector<Vertex>& clippingWindow) override;

        void printDescription() const override;

};







#endif  // PRIMITIVE_H