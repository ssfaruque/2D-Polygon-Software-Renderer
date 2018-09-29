#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include "intTypes.h"

class FrameBuffer
{
    private:
        u32* m_buffer;

    public:
        FrameBuffer(uint width, uint height);
        ~FrameBuffer();

    friend class Window;
};



#endif  // FRAME_BUFFER_H