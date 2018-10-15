#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <iostream>
#include <vector>

#include "entity.h"


class Line : public Entity
{
    private:

    public:
        Line(const Vertex& v1, const Vertex& v2, Color color = Color(0xFFFFFFFF), bool drawWithBresenham = false);
        Line();
        
        void draw(const std::vector<Vertex>& clippingWindow) override;
        void printDescription() const override;
};


class Polygon : public Entity
{
    private:
        bool m_rasterized;  // if true, polygon will be filled

    public:
        Polygon(const std::vector<Vertex>& vertices, Color color = Color(0xFFFFFFFF), bool drawWithBresenham = false, bool rasterized = false);
        Polygon();

        void draw(const std::vector<Vertex>& clippingWindow) override;
        void printDescription() const override;
        inline void setRasterizationStatus(bool rasterized) {m_rasterized = rasterized;}

};



#endif  // PRIMITIVE_H