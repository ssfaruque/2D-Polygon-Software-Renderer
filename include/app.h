#ifndef APP_H
#define APP_H

class Window;


class App
{
    private:
        bool m_running;

    public:
        App(const char* TITLE, const int WIDTH, const int HEIGHT,
            int* argc, char** argv);
        ~App() = default;
        inline bool isRunning() const {return m_running;};

    
};






#endif  // APP_H