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
        static Window* m_window;

    private:
        Window(uint width, uint height, std::string title, int* argc, char** argv);

    public:
        ~Window();
        static void create(uint width, uint height, std::string title, int* argc, char** argv);
        static Window* getInstance();
        static void destroy();
        inline uint getWidth() const {return m_width;};
        inline uint getHeight() const {return m_height;};
        FrameBuffer* getFrameBuffer() {return m_frameBuffer;}


    
};




#endif  // WINDOW_H