#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>

#include "types.h"

enum LineMethod
{
    DDA,
    BRESENHAM
};


/*
 * Converts normalized device coordinates
 * into screen coordinates
 */
void normalToScreenCoords(float* x, float* y);


/*
 * Converts clipped coordinates
 * into normalized device coordinates
 */
void clipToNormalCoords(float* x, float* y, float xmin, float xmax, float ymin, float ymax); 


/*
 * Draws a single pixel to the frame buffer
 */
void drawPixel(float x, float y, Color color, bool normalized = false);


/*
 * Draws a line to the frame buffer given starting and ending coordinates
 */
void drawLine(uint x1, uint y1, uint x2, uint y2, Color color, bool drawWithBresenham);


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
void polygonFill(const std::vector<Vertex>& vertices, Color color);


/*
 * Implementation of Cohen-Sutherland line clipping algorithm
 */
void cohenSutherlandClipping(const std::vector<Vertex>& vertices, float xmin, float xmax, float ymin, float ymax, Color color = 0xFFFFFFFF, LineMethod method = BRESENHAM);



/*
 * Implementation of Sutherland-Hodgman line clipping algorithm
 */
std::vector<Vertex> sutherlandHodgmanClipping(const std::vector<Vertex>& vertices, const std::vector<Vertex>& clippingWindow);


#endif  // GRAPHICS_H