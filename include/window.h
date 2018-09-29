#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include "intTypes.h"

class FrameBuffer;

class Window
{
    private:
        uint m_width;
        uint m_height;
        std::string m_title;
        FrameBuffer* m_frameBuffer;

    public:
        Window(uint width, uint height, std::string title, int* argc, char** argv);
        ~Window();
    
};




#endif  // WINDOW_H