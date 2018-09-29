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
     * coordinate (0,0) being in the upper left hand
     * corner of the screen with x increasing from left
     * to right and y increasing from top to botttom
     */
    uint index = (m_width * m_height) - y * m_width + x;
    m_buffer[index] = data;
}


void FrameBuffer::clear(Color color)
{
    for(uint i = 0; i < m_width * m_height; ++i)
        m_buffer[i] = color.color;
}
