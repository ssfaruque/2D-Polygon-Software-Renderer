#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#ifdef __linux__
#include <GL/glut.h>
#endif

#include <cassert>
#include <iostream>
#include <algorithm>

#include "graphics.h"
#include "window.h"
#include "frameBuffer.h"
#include "math.h"


void bresenhamSmallSlope(uint x1, uint y1, uint x2, uint y2, Color color);
void bresenhamHighSlope(uint x1, uint y1, uint x2, uint y2, Color color);


inline uint absVal(int num) { return num > 0 ? num : (num * -1); }


void normalToScreenCoords(float* x, float* y)
{
    Window *window = Window::getInstance();
    *x = (window->getFrameBuffer()->getWidth() / 2) * (*x + 1);
    *y = (window->getFrameBuffer()->getHeight() / 2) * (*y + 1);

    // clamp x and y to boundaries, index in array starts at 0
    *x = uint(*x) == window->getFrameBuffer()->getWidth()  ? window->getFrameBuffer()->getWidth()  - 1 : *x;
    *y = uint(*y) == window->getFrameBuffer()->getHeight() ? window->getFrameBuffer()->getHeight() - 1 : *y;
}


void clipToNormalCoords(float* x, float* y, float xmin, float xmax, float ymin, float ymax) 
{
    float clipWidth  = xmax - xmin;
    float clipHeight = ymax - ymin;

    *x = 2 * ((*x - xmax) / clipWidth)  + 1;
    *y = 2 * ((*y - ymax) / clipHeight) + 1;
} 


void drawPixel(float x, float y, Color color, bool normalized)
{
    Window *window = Window::getInstance();
    if (normalized){normalToScreenCoords(&x, &y);}

    if (!(x >= 0 && x <= window->getFrameBuffer()->getWidth() && y >= 0 && y <= window->getFrameBuffer()->getHeight()))
    {
        std::cout << "** pixel out of bounds **" << std::endl;
        std::cout << "Screen coords -> "
                  << "x: " << x << ", y: " << y << std::endl
                  << std::endl;
    }

    window->getFrameBuffer()->setPixel(x, y, color.color);
}


void drawLine(uint x1, uint y1, uint x2, uint y2, Color color, bool drawWithBresenham)
{
    if(drawWithBresenham)   bresenham(x1, y1, x2, y2, color);
    else                    dda(x1, y1, x2, y2, color);
}


void dda(float x1, float y1, float x2, float y2, Color color)
{
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    int numSteps = absVal(deltaX) > absVal(deltaY) ? absVal(deltaX) : absVal(deltaY);
    float xStep = (float)(deltaX) / (float)(numSteps);
    float yStep = (float)(deltaY) / (float)(numSteps);
    float roundTerm = 0.5f; /* E.g. If number is 4.6, adding 0.5 will
                             * result in 5.1 and will be rounded
                             * down to 5 when casted to a uint
                             */
    float x = x1;
    float y = y1;

    for (int step = 0; step < numSteps; ++step)
    {
        drawPixel((x + roundTerm), (y + roundTerm), color, false);
        x += xStep;
        y += yStep;
    }
}


void bresenham(float x1, float y1, float x2, float y2, Color color)
{
    int absDeltaX = absVal(x2 - x1);
    int absDeltaY = absVal(y2 - y1);

    if(absDeltaY < absDeltaX)   // slope < 1
    {
        // switch order of parameters depending on order of vertices
        x1 < x2 ?
        bresenhamSmallSlope(x1, y1, x2, y2, color) :
        bresenhamSmallSlope(x2, y2, x1, y1, color);
    }

    else    // slope >= 1
    {
        // switch order of parameters depending on order of vertices
        y1 < y2 ?
        bresenhamHighSlope(x1, y1, x2, y2, color) :
        bresenhamHighSlope(x2, y2, x1, y1, color);
    }
}


// When slope < 1
void bresenhamSmallSlope(uint x1, uint y1, uint x2, uint y2, Color color)
{
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    int yInc = (deltaY >= 0) ? 1 : -1;
    deltaY = (deltaY >= 0) ? deltaY : -deltaY;

    int error = 2 * deltaY - deltaX;

    for (uint x = x1, y = y1; x <= x2; ++x)
    {
        drawPixel(x, y, color, false);

        if (error > 0)
        {
            y += yInc;
            error -= (2 * deltaX);
        }

        error += (2 * deltaY);
    }
}


// When slope >= 1
void bresenhamHighSlope(uint x1, uint y1, uint x2, uint y2, Color color)
{
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    int xInc = (deltaX >= 0) ? 1 : -1;
    deltaX = (deltaX >= 0) ? deltaX : -deltaX;

    int error = 2 * deltaX - deltaY;

    for (uint y = y1, x = x1; y <= y2; ++y)
    {
        drawPixel(x, y, color, false);

        if (error > 0)
        {
            x += xInc;
            error -= (2 * deltaY);
        }

        error += (2 * deltaX);
    }
}


std::vector<Edge> createEdges(const std::vector<Vertex>& vertices)
{
    std::vector<Edge> edges{};

    for(int i = 0; i < (int)vertices.size(); ++i)
    {
        float yMax, yMin, startingX, slopeInv;

        if(i == (int)(vertices.size() - 1))
        {
            yMax = uint(vertices[i].y) > uint(vertices[0].y) ? vertices[i].y : vertices[0].y;
            yMin = uint(vertices[i].y) < uint(vertices[0].y) ? vertices[i].y : vertices[0].y;
            startingX = uint(yMin) == uint(vertices[i].y) ? vertices[i].x : vertices[0]. x;
            slopeInv = uint(vertices[i].x) < uint(vertices[0].x) ?
                    (vertices[0].x - vertices[i].x) / (vertices[0].y - vertices[i].y) :
                    (vertices[i].x - vertices[0].x) / (vertices[i].y - vertices[0].y);                    
        }

        else
        {
            yMax = uint(vertices[i].y) > uint(vertices[i + 1].y) ? vertices[i].y : vertices[i + 1].y;
            yMin = uint(vertices[i].y) < uint(vertices[i + 1].y) ? vertices[i].y : vertices[i + 1].y;
            startingX = uint(yMin) == uint(vertices[i].y) ? vertices[i].x : vertices[i + 1].x;
            slopeInv = uint(vertices[i].x) < uint(vertices[i + 1].x) ?
                    (vertices[i + 1].x - vertices[i].x) / (vertices[i + 1].y - vertices[i].y) :
                    (vertices[i].x - vertices[i + 1].x) /(vertices[i].y - vertices[i + 1].y);
        }

        // don't include horizontal edges
        if(uint(yMin) == uint(yMax)) continue;

        edges.emplace_back(yMax, yMin, startingX, slopeInv);
    }

    std::sort(edges.begin(),
              edges.end(),
              [](const Edge& e1, const Edge& e2)
              {return uint(e1.yMin) < uint(e2.yMin);});

    return edges;
}


std::vector<std::vector<Edge>> createEdgeList(const std::vector<Edge>& edges)
{
    uint yMin = edges[0].yMin, yMax = edges[0].yMax;

    for(auto& edge : edges)
    {
        if(uint(yMax) < uint(edge.yMax)) yMax = edge.yMax;
        if(uint(yMin) > uint(edge.yMin)) yMin = edge.yMin;
    }

    // allocate size to total num of scanlines
    std::vector<std::vector<Edge>> edgeList(yMax - yMin + 1); 

    for(uint scanLine = yMin; scanLine <= yMax; ++scanLine)
    {
        int index = scanLine - yMin;

        for(auto& edge : edges)
        {
            // add to active edge list
            if(scanLine == uint(edge.yMin))
                edgeList[index].push_back(edge);
        }

        sort(edgeList[index].begin(),
             edgeList[index].end(),
             [](const Edge& e1, const Edge& e2)
             {return uint(e1.startingX) < uint(e2.startingX);});
    }

    return edgeList;   
}



void printEdges(const std::vector<Edge>& edgeList)
{
    std::cout << "** CONTENTS OF EDGE LIST **" << std::endl;
    for(auto& edge : edgeList)
    {
        std::cout << "starting x: " << edge.startingX << ", " 
                  << "slope: " << 1 / edge.slopeInv << ", "
                  << "yMin: " << edge.yMin << ", "
                  << "yMax: " << edge.yMax << std::endl;                 
    }
    std::cout << std::endl;
}


// removes all edges that have a yMax equivalent to the given scanLine value
void cleanActiveEdgeList(std::vector<Edge>& activeEdgeList, uint scanLine)
{
    auto newEnd = std::remove_if(activeEdgeList.begin(),
                        activeEdgeList.end(),
                        [scanLine](const Edge& e) {return uint(e.yMax) == uint(scanLine);});
    activeEdgeList.erase(newEnd, activeEdgeList.end());
}


void polygonFill(const std::vector<Vertex>& vertices, Color color)
{
    // supposed to add only non horizontal edges to table
    std::vector<Edge> edges = createEdges(vertices);
    std::vector<std::vector<Edge>> edgeList = createEdgeList(edges);

    int yMin = edges[0].yMin, yMax = edges[0].yMax;

    for(auto& edge : edges)
    {
        if(uint(yMax) < uint(edge.yMax)) yMax = edge.yMax;
        if(uint(yMin) > uint(edge.yMin)) yMin = edge.yMin;
    }

    std::vector<Edge> activeEdgeList{};

    for(int scanLine = yMin; scanLine <= yMax; ++scanLine)
    {
        int index = scanLine - yMin;

        // adds new edges to active edge list
        if(!edgeList[index].empty())
        {
            for(auto& edge : edgeList[index])
                activeEdgeList.push_back(edge);
        }

        cleanActiveEdgeList(activeEdgeList, scanLine);
        std::sort(activeEdgeList.begin(),
                  activeEdgeList.end(),
                  [](const Edge& e1, const Edge& e2){return uint(e1.startingX) < uint(e2.startingX);});

        if(activeEdgeList.size() > 1 && scanLine != yMin)
        {
            for(int i = 0; i < (int)activeEdgeList.size(); i += 2)
            {
                for(uint x1 = activeEdgeList[i].startingX + 1,
                    x2 = activeEdgeList[i + 1].startingX;
                    x1 < x2;
                     ++x1)
                        drawPixel(x1, scanLine, color, false);
            }
        }
        
        cleanActiveEdgeList(activeEdgeList, scanLine);

        for(auto& edge : activeEdgeList)
            edge.startingX += edge.slopeInv;
    }
}


enum ClipWindowCode
{
    LEFT    = 1 << 0,
    RIGHT   = 1 << 1,
    BOTTOM  = 1 << 2,
    TOP     = 1 << 3
};


uint calcCoding(float x, float y, float xmin, float xmax, float ymin, float ymax)
{
    uint coding =  0;

    if(x < xmin) coding |= LEFT;
    else if(x > xmax) coding |= RIGHT;
    if(y < ymin) coding |= BOTTOM;
    else if(y > ymax) coding |= TOP;

    return coding;
}


inline bool isInside(uint code1, uint code2)  {return !(code1 | code2);}
inline bool isOutside(uint code1, uint code2) {return (code1 & code2);}

void cohenSutherlandClipping(Vertex* v1, Vertex* v2, float xmin, float xmax, float ymin, float ymax)
{
    float boundaryOffset = 0.0000001f;

    uint code1 = calcCoding(v1->x, v1->y, xmin, xmax, ymin, ymax);
    uint code2 = calcCoding(v2->x, v2->y, xmin, xmax, ymin, ymax);

    while (true)
    {
        if (isInside(code1, code2) || isOutside(code1, code2))
            break;

        else // partially inside clipping window
        {
            uint outsideCoding = code1 ? code1 : code2;
            float x = 0.0f, y = 0.0f;

            if (outsideCoding & LEFT)
            {
                y = v1->y + (v2->y - v1->y) * (xmin - v1->x) / (v2->x - v1->x);
                x = xmin + boundaryOffset;
            }

            else if (outsideCoding & RIGHT)
            {
                y = v1->y + (v2->y - v1->y) * (xmax - v1->x) / (v2->x - v1->x);
                x = xmax - boundaryOffset;
            }

            else if (outsideCoding & BOTTOM)
            {
                x = v1->x + (v2->x - v1->x) * (ymin - v1->y) / (v2->y - v1->y);
                y = ymin + boundaryOffset;
            }

            else if (outsideCoding & TOP)
            {
                x = v1->x + (v2->x - v1->x) * (ymax - v1->y) / (v2->y - v1->y);
                y = ymax - boundaryOffset;
            }

            if (code1 == outsideCoding)
            {
                v1->x = x;
                v1->y = y;
                code1 = calcCoding(v1->x, v1->y, xmin, xmax, ymin, ymax);
            }

            else
            {
                v2->x = x;
                v2->y = y;
                code2 = calcCoding(v2->x, v2->y, xmin, xmax, ymin, ymax);
            }
        }
    }
}


Vertex intersectionPoint(const Vertex& p1, const Vertex& p2,
                      const Vertex& p3, const Vertex& p4)
{
    Vertex intersection;

    float xCoordNumerator = (p1.x * p2.y - p1.y * p2.x) * (p3.x - p4.x) - (p1.x - p2.x) * (p3.x * p4.y - p3.y * p4.x); 
    float yCoordNumerator = (p1.x * p2.y - p1.y * p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x * p4.y - p3.y * p4.x); 
    float denominator     = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);

    intersection.x = xCoordNumerator / denominator;
    intersection.y = yCoordNumerator / denominator;

    return intersection;
}


std::vector<Vertex> clipPointsWithWindow(const std::vector<Vertex>& vertices, const Vertex& clipV1, const Vertex& clipV2)
{
    std::vector<Vertex> clippedVertices{};

    for(uint i = 0, size = uint(vertices.size()); i < size; ++i)
    {
        uint j = (i == (size - 1)) ? 0 : (i + 1);
        Vertex v1 = vertices[i];
        Vertex v2 = vertices[j];

        float p1 = (clipV2.x - clipV1.x) * (v1.y - clipV1.y) - (clipV2.y - clipV1.y) * (v1.x - clipV1.x);
        float p2 = (clipV2.x - clipV1.x) * (v2.y - clipV1.y) - (clipV2.y - clipV1.y) * (v2.x - clipV1.x);


        if(p1 < 0 && p2 < 0)
            clippedVertices.push_back(v2);

        else if(p1 >= 0 && p2 < 0)
        {
            clippedVertices.push_back(intersectionPoint(v1, v2, clipV1, clipV2));
            clippedVertices.push_back(v2);
        }

        else if(p1 < 0 && p2 >= 0)
            clippedVertices.push_back(intersectionPoint(v1, v2, clipV1, clipV2)); 
    }

    return clippedVertices;
}


std::vector<Vertex> sutherlandHodgmanClipping(const std::vector<Vertex>& vertices, const std::vector<Vertex>& clippingWindow)
{
    std::vector<Vertex> clippedVertices = vertices;

    for(uint i = 0, size = uint(clippingWindow.size()); i < size; ++i)
    {   
        uint j = (i == (size - 1)) ? 0 : (i + 1);
        clippedVertices = clipPointsWithWindow(clippedVertices, clippingWindow[i], clippingWindow[j]);
    }

    return clippedVertices;
}
