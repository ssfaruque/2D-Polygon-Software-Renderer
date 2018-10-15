#include <algorithm>
#include <iomanip>

#include "primitive.h"
#include "graphics.h"

Line::Line(const Vertex &v1, const Vertex &v2, Color color, bool drawWithBresenham)

{
    m_drawWithBresenham = drawWithBresenham;
    m_vertices.push_back(v1);
    m_vertices.push_back(v2);
    m_color = color;
}


Line::Line()
{
}


Polygon::Polygon(const std::vector<Vertex> &vertices, Color color, bool drawWithBresenham, bool rasterized) : m_rasterized(rasterized)
{
    m_drawWithBresenham = drawWithBresenham;
    m_vertices = vertices;
    m_color = color;
}


Polygon::Polygon(): m_rasterized(false)
{
}


void Line::draw(const std::vector<Vertex>& clippingWindow)
{
    float xmin = clippingWindow[0].x, xmax = clippingWindow[0].x;
    float ymin = clippingWindow[0].y, ymax = clippingWindow[0].y;

    for(const auto& vertex : clippingWindow)
    {
        xmin = vertex.x < xmin ? vertex.x : xmin;
        xmax = vertex.x > xmax ? vertex.x : xmax;
        ymin = vertex.y < ymin ? vertex.y : ymin;
        ymax = vertex.y > ymax ? vertex.y : ymax;
    }

    Vertex v1 = m_vertices[0];
    Vertex v2 = m_vertices[1];

    cohenSutherlandClipping(&v1, &v2, xmin, xmax, ymin, ymax);

    float x1 = v1.x, y1 = v1.y,
          x2 = v2.x, y2 = v2.y;

    clipToNormalCoords(&x1, &y1, xmin, xmax, ymin, ymax);
    clipToNormalCoords(&x2, &y2, xmin, xmax, ymin, ymax);
    normalToScreenCoords(&x1, &y1);
    normalToScreenCoords(&x2, &y2);

    drawLine(x1, y1, x2, y2, m_color, m_drawWithBresenham);
}


void Polygon::draw(const std::vector<Vertex>& clippingWindow)
{
    std::vector<Vertex> vertices = sutherlandHodgmanClipping(m_vertices, clippingWindow);

    float xmin = clippingWindow[0].x, xmax = clippingWindow[0].x;
    float ymin = clippingWindow[0].y, ymax = clippingWindow[0].y;

    for(const auto& vertex : clippingWindow)
    {
        xmin = vertex.x < xmin ? vertex.x : xmin;
        xmax = vertex.x > xmax ? vertex.x : xmax;
        ymin = vertex.y < ymin ? vertex.y : ymin;
        ymax = vertex.y > ymax ? vertex.y : ymax;
    }

    if(!vertices.empty())
    {
        for(int i = 0, size = int(vertices.size()); i < size; ++i)
        {
            float x1 = 0.0f, y1 = 0.0f, x2 = 0.0f, y2 = 0.0f;

            if(i == size - 1)
            {
                x1 = vertices[i].x;
                y1 = vertices[i].y;
                x2 = vertices[0].x;
                y2 = vertices[0].y;  
            }
            
            else
            {
                x1 = vertices[i].x;
                y1 = vertices[i].y;
                x2 = vertices[i + 1].x;
                y2 = vertices[i + 1].y;
            }

            clipToNormalCoords(&x1, &y1, xmin, xmax, ymin, ymax);
            clipToNormalCoords(&x2, &y2, xmin, xmax, ymin, ymax);
            normalToScreenCoords(&x1, &y1);
            normalToScreenCoords(&x2, &y2);    
            drawLine(x1, y1, x2, y2, m_color, m_drawWithBresenham);
        }

        if(m_rasterized)
        {
            for(auto& vertex : vertices)
            {
                clipToNormalCoords(&vertex.x, &vertex.y, xmin, xmax, ymin, ymax);

                normalToScreenCoords(&vertex.x, &vertex.y);
            }

            polygonFill(vertices, m_color);
        }
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
