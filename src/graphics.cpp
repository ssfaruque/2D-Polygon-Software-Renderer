#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#ifdef __linux__
#include <GL/glut.h>
#endif

#include <cassert>
#include <iostream>
#include <algorithm>

#include "window.h"
#include "frameBuffer.h"
#include "graphics.h"


void bresenhamSmallSlope(uint x1, uint y1, uint x2, uint y2, Color color);
void bresenhamHighSlope(uint x1, uint y1, uint x2, uint y2, Color color);


inline uint absVal(int num) { return num > 0 ? num : (num * -1); }


void normalToScreenCoords(float* x, float* y)
{
    Window *window = Window::getInstance();
    *x = (window->getWidth() / 2) * (*x + 1);
    *y = (window->getHeight() / 2) * (*y + 1);
}


void drawPixel(float x, float y, Color color, bool normalized)
{
    Window *window = Window::getInstance();
    if (normalized){normalToScreenCoords(&x, &y);}

    if (!(x >= 0 && x <= window->getWidth() && y >= 0 && y <= window->getHeight()))
    {
        std::cout << "** pixel out of bounds **" << std::endl;
        std::cout << "Screen coords -> "
                  << "x: " << x << ", y: " << y << std::endl
                  << std::endl;
    }

    window->getFrameBuffer()->setPixel(x, y, color.color);
}


void drawLine(uint x1, uint y1, uint x2, uint y2, Color color)
{
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    int numSteps = absVal(deltaX) > absVal(deltaY) ? absVal(deltaX) : absVal(deltaY);
    float xStep = (float)(deltaX) / (float)(numSteps);
    float yStep = (float)(deltaY) / (float)(numSteps);
    float roundTerm = 0.5f;
    float x = x1;
    float y = y1;

    for (int step = 0; step < numSteps; ++step)
    {
        drawPixel((uint)(x + roundTerm), (uint)(y + roundTerm), color);
        x += xStep;
        y += yStep;
    }
}






void dda(float x1, float y1, float x2, float y2, Color color)
{
    normalToScreenCoords(&x1, &y1);
    normalToScreenCoords(&x2, &y2);

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
        drawPixel((uint)(x + roundTerm), (uint)(y + roundTerm), color, false);
        x += xStep;
        y += yStep;
    }
}







void bresenham(float x1, float y1, float x2, float y2, Color color)
{
    normalToScreenCoords(&x1, &y1);
    normalToScreenCoords(&x2, &y2);

    int absDeltaX = absVal(x2 - x1);
    int absDeltaY = absVal(y2 - y1);

    if(absDeltaY < absDeltaX)   // slope < 1
    {
        x1 < x2 ?
        bresenhamSmallSlope(x1, y1, x2, y2, color) :
        bresenhamSmallSlope(x2, y2, x1, y1, color);
    }

    else    // slope >= 1
    {
        y1 < y2 ?
        bresenhamHighSlope(x1, y1, x2, y2, color) :
        bresenhamHighSlope(x2, y2, x1, y1, color);
    }
}


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
            yMax = vertices[i].y > vertices[0].y ? vertices[i].y : vertices[0].y;
            yMin = vertices[i].y < vertices[0].y ? vertices[i].y : vertices[0].y;
            startingX = yMin == vertices[i].y ? vertices[i].x : vertices[0]. x;
            slopeInv = vertices[i].x < vertices[0].x ?
                    (vertices[0].x - vertices[i].x) / (vertices[0].y - vertices[i].y) :
                    (vertices[i].x - vertices[0].x) / (vertices[i].y - vertices[0].y);                    
        }

        else
        {
            yMax = vertices[i].y > vertices[i + 1].y ? vertices[i].y : vertices[i + 1].y;
            yMin = vertices[i].y < vertices[i + 1].y ? vertices[i].y : vertices[i + 1].y;
            startingX = yMin == vertices[i].y ? vertices[i].x : vertices[i + 1].x;
            slopeInv = vertices[i].x < vertices[i + 1].x ?
                    (vertices[i + 1].x - vertices[i].x) / (vertices[i + 1].y - vertices[i].y) :
                    (vertices[i].x - vertices[i + 1].x) /(vertices[i].y - vertices[i + 1].y);
        }

        // don't include horizontal edges
        if((int)yMin == (int)yMax) continue;

        edges.emplace_back(yMax, yMin, startingX, slopeInv);
    }

    std::sort(edges.begin(),
              edges.end(),
              [](const Edge& e1, const Edge& e2)
              {return e1.yMin < e2.yMin;});

    return edges;
}


std::vector<std::vector<Edge>> createEdgeList(const std::vector<Edge>& edges)
{
    float yMin = edges[0].yMin, yMax = edges[0].yMax;

    for(auto& edge : edges)
    {
        if(yMax < edge.yMax) yMax = edge.yMax;
        if(yMin > edge.yMin) yMin = edge.yMin;
    }

    // std::cout << "Lowest y point: " << yMin << std::endl;
    // std::cout << "Highest y point: " << yMax << std::endl << std::endl;

    // allocate size to total num of scanlines
    std::vector<std::vector<Edge>> edgeList(yMax - yMin + 1); 

    for(int scanLine = yMin; scanLine <= yMax; ++scanLine)
    {
        int index = scanLine - yMin;

        for(auto& edge : edges)
        {
            // add to active edge list
            if(scanLine == edge.yMin)
                edgeList[index].push_back(edge);
        }

        sort(edgeList[index].begin(),
             edgeList[index].end(),
             [](const Edge& e1, const Edge& e2)
             {return e1.startingX < e2.startingX;});
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


void polygonFill(const std::vector<Vertex>& vertices, Color color)
{
    // supposed to add only non horizontal edges to table
    std::vector<Edge> edges = createEdges(vertices);
    printEdges(edges);
    std::vector<std::vector<Edge>> edgeList = createEdgeList(edges);

    float yMin = edges[0].yMin, yMax = edges[0].yMax;

    for(auto& edge : edges)
    {
        if(yMax < edge.yMax) yMax = edge.yMax;
        if(yMin > edge.yMin) yMin = edge.yMin;
    }

    std::vector<Edge> activeEdgeList{};

    for(int scanLine = yMin; scanLine <= yMax; ++scanLine)
    {
        // y Max - 250


        if(scanLine == yMax - 252)
        {
            std::cout << "Start debugging here" << std::endl;
        }

        int index = scanLine - yMin;

        // adds new edges to active edge list
        if(!edgeList[index].empty())
        {
            for(auto& edge : edgeList[index])
                activeEdgeList.push_back(edge);
        }

        std::sort(activeEdgeList.begin(),
                  activeEdgeList.end(),
                  [](const Edge& e1, const Edge& e2){return e1.startingX < e2.startingX;});


        if(activeEdgeList.size() > 1)
        {
            for(int i = 0; i < (int)activeEdgeList.size(); i += 2)
            {
                for(float x1 = activeEdgeList[i].startingX,
                    x2 = activeEdgeList[i + 1].startingX;
                    x1 < x2;
                     ++x1)
                        drawPixel(x1, scanLine, color, false);
                     
            }
        }
        
        // removes all edges in active edge list that we are finished with
        auto newEnd = std::remove_if(activeEdgeList.begin(),
                        activeEdgeList.end(),
                        [&scanLine](const Edge& e) {return uint(e.yMax) == uint(scanLine);});

        activeEdgeList.erase(newEnd, activeEdgeList.end());

        for(auto& edge : activeEdgeList)
            edge.startingX += edge.slopeInv;
    }
}

