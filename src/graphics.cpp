#ifdef __APPLE__
#include <GLUT/glut.h>
#endif
#ifdef __linux__
#include <GL/glut.h>
#endif

#include <cassert>
#include <iostream>

#include "window.h"
#include "frameBuffer.h"
#include "graphics.h"


void bresenhamSmallSlope(uint x1, uint y1, uint x2, uint y2, Color color);
void bresenhamHighSlope(uint x1, uint y1, uint x2, uint y2, Color color);


inline uint absVal(int num) { return num > 0 ? num : (num * -1); }


void normalToScreenCoords(float *x, float *y)
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
