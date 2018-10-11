#include <iomanip>

#include "primitive.h"
#include "graphics.h"

void Line::draw()
{
    float x1 = m_vertices[0].x, y1 = m_vertices[0].y,
          x2 = m_vertices[1].x, y2 = m_vertices[1].y;
    normalToScreenCoords(&x1, &y1);
    normalToScreenCoords(&x2, &y2);
    drawLine(x1, y1, x2, y2, m_color, m_drawWithBresenham);
}


void Polygon::draw()
{
    for(int i = 0, size = int(m_vertices.size()); i < size; ++i)
    {
        float x1 = 0.0f, y1 = 0.0f, x2 = 0.0f, y2 = 0.0f;

        if(i == size - 1)
        {
            x1 = m_vertices[i].x;
            y1 = m_vertices[i].y;
            x2 = m_vertices[0].x;
            y2 = m_vertices[0].y;  
        }
        
        else
        {
            x1 = m_vertices[i].x;
            y1 = m_vertices[i].y;
            x2 = m_vertices[i + 1].x;
            y2 = m_vertices[i + 1].y;
        }

        normalToScreenCoords(&x1, &y1);
        normalToScreenCoords(&x2, &y2);    
        drawLine(x1, y1,
                     x2, y2,
                     0xffffffff, m_drawWithBresenham);
    }

    if(m_rasterized)
    {
        std::vector<Vertex> vertices = m_vertices;

        for(auto& vertex : vertices)
            normalToScreenCoords(&vertex.x, &vertex.y);

        polygonFill(vertices, m_color);
    }
}




void Line::printDescription() const
{
    std::cout << "ID: " << std::setw(10) << std::left << m_id 
              << " type: " << std::setw(10) << "Line "
              << " vertices: " 
              << "(" << m_vertices[0].x << ", " << m_vertices[0].y << ") "
              << "(" << m_vertices[1].x << ", " << m_vertices[1].y << ") " << std::endl;;
}


void Polygon::printDescription() const
{
    std::cout << "ID: " << std::setw(10) << std::left << m_id 
              << " type: " << std::setw(10) << "Polygon "
              << "numSides: " << getNumVertices() << std::endl;
}


