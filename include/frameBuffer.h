#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include "intTypes.h"

class FrameBuffer
{
    private:
        u32* m_buffer;  // index 0 starts at lower left hand corner of screen
        uint m_width;
        uint m_height;

    public:
        FrameBuffer(uint width, uint height);
        ~FrameBuffer();
        void setPixel(uint x, uint y, u32 data);
        inline u32* getBuffer() const {return m_buffer;}

    friend class Window;
};



#endif  // FRAME_BUFFER_H