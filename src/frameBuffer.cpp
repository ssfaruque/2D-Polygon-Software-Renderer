#include <cstring>

#include "frameBuffer.h"

FrameBuffer::FrameBuffer(uint width, uint height):
m_width(width), m_height(height)
{
    m_buffer = new u32[width * height];

    memset(m_buffer, 0, sizeof(u32) * width * height);    
}


FrameBuffer::~FrameBuffer()
{
    if(m_buffer)
        delete [] m_buffer;
}


void FrameBuffer::setPixel(uint x, uint y, u32 data)
{
    /* This method of indexing results in
     * coordinate (0,0) being the upper left hand
     * corner of the screen with x increasing from left
     * to right and y increasing from top to botttom
     */
    uint index = (m_width * m_height) - x * m_width + y;
    m_buffer[index] = data;
}