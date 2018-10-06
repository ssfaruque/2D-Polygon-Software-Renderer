#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>

#include "types.h"

/*
 * Converts normalized device coordinates
 * into screen coordinates
 */
void normalToScreenCoords(float* x, float* y);




/*
 * Draws a single pixel to the frame buffer
 */
void drawPixel(float x, float y, Color color, bool normalized = true);



/*
 * Draws a line to the frame buffer given starting and ending coordinates
 */
void drawLine(uint x1, uint y1, uint x2, uint y2, Color color);


/*
 * Implementation of DDA algorithm
 */
void dda(float x1, float y1, float x2, float y2, Color color);


/*
 * Implementation of Bresenham algorithm
 */
void bresenham(float x1, float y1, float x2, float y2, Color color);



/*
 * Implementation of scan line polygon fill algorithm
 */
void polygonFill(const std::vector<Vertex>& vertices);




#endif  // GRAPHICS_H