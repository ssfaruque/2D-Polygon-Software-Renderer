#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "types.h"

/*
 * Draws a single pixel to the frame buffer
 */
void drawPixel(uint x, uint y, Color color);

/*
 * Implementation of DDA algorithm
 */
void drawLine(uint x1, uint y1, uint x2, uint y2, Color color);


#endif  // GRAPHICS_H