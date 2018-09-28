#ifndef APP_H
#define APP_H

class App
{
    private:
        bool m_running;

    public:
        App(int* argc, char** argv);
        ~App() = default;
        inline bool isRunning() const {return m_running;};

    
};






#endif  // APP_H