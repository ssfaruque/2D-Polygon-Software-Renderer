#include <GL/freeglut.h>

#include "graphics.h"
#include "window.h"

void setPointSize(float size)
{
    glPointSize(size);
}


 void drawPixel(uint x, uint y, u8 r, u8 g, u8 b, u8 a)
 {
    //  float normalizedX;
    //  float normalizedY;

     glBegin(GL_POINTS);

     glColor4f(r, g, b, a);
     glVertex2f(0.0f, 0.0f);

     glEnd();
 }               