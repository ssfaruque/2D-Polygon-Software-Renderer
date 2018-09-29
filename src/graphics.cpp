#include <GL/freeglut.h>
#include <cassert>

#include "window.h"
#include "frameBuffer.h"
#include "graphics.h"



 void drawPixel(uint x, uint y, Color color)
 {
    Window* window = Window::getInstance();

    window->getFrameBuffer()->setPixel(x, y, color.color);
 }               


 void drawLine(uint x1, uint y1, uint x2, uint y2, Color color)
 {
    int deltaX  = x2 - x1;
    int deltaY  = y2 - y1;
    //float slope = deltaY / deltaX;

    int numSteps = deltaX > deltaY ? deltaX : deltaY;
    float xStep = deltaX / numSteps;
    float yStep = deltaY / numSteps;
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
