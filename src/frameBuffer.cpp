#include "frameBuffer.h"

FrameBuffer::FrameBuffer(uint width, uint height)
{
    m_buffer = new u32[width * height];
}


FrameBuffer::~FrameBuffer()
{
    if(m_buffer)
        delete [] m_buffer;
}

