#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "types.h"

/*
 * Draws a single pixel to the frame buffer
 */
void drawPixel(uint x, uint y, Color color);


/*
 * Draws a line to the frame buffer given starting and ending coordinates
 */
void drawLine(uint x1, uint y1, uint x2, uint y2, Color color);


/*
 * Implementation of DDA algorithm
 */
void dda(uint x1, uint y1, uint x2, uint y2, Color color);


/*
 * Implementation of Bresenham algorithm
 */
void bresenham(uint x1, uint y1, uint x2, uint y2, Color color);

#endif  // GRAPHICS_H