#include <GL/freeglut.h>
#include <cassert>

#include "window.h"
#include "frameBuffer.h"
#include "graphics.h"


inline uint absVal(int num) {return num > 0 ? num : (num * -1);}

 void drawPixel(uint x, uint y, Color color)
 {
    Window* window = Window::getInstance();
    assert( x >=0 && x <= window->getWidth() && y >=0 && y <= window->getHeight());
    window->getFrameBuffer()->setPixel(x, y, color.color);
 }               


 void drawLine(uint x1, uint y1, uint x2, uint y2, Color color)
 {
    int deltaX  = x2 - x1;
    int deltaY  = y2 - y1;
    int numSteps = absVal(deltaX) > absVal(deltaY) ? absVal(deltaX) : absVal(deltaY);
    float xStep = (float)(deltaX) / (float)(numSteps);
    float yStep = (float)(deltaY) / (float)(numSteps);
    float roundTerm = 0.5f;
    float x = x1;
    float y = y1;

    for(int step = 0; step < numSteps; ++step)
    {
        drawPixel((uint)(x + roundTerm), (uint)(y + roundTerm), color);
        x += xStep;
        y += yStep;
    }
 }


void DDA(uint x1, uint y1, uint x2, uint y2, Color color)
{
    int deltaX  = x2 - x1;
    int deltaY  = y2 - y1;
    int numSteps = absVal(deltaX) > absVal(deltaY) ? absVal(deltaX) : absVal(deltaY);
    float xStep = (float)(deltaX) / (float)(numSteps);
    float yStep = (float)(deltaY) / (float)(numSteps);
    float roundTerm = 0.5f;
    float x = x1;
    float y = y1;

    for(int step = 0; step < numSteps; ++step)
    {
        drawPixel((uint)(x + roundTerm), (uint)(y + roundTerm), color);
        x += xStep;
        y += yStep;
    }   
}


void bresenham(uint x1, uint y1, uint x2, uint y2, Color color)
{
    
}