#ifndef APP_H
#define APP_H

class Window;

class App
{
    private:
        bool m_running;
        Window* m_window;

    public:
        App(const char* title, const int width, const int height,
            int* argc, char** argv);
        ~App();
        inline bool isRunning() const {return m_running;};

        /* Reigster necessary callbacks and
         * run main loop
         */
        void run();
};


#endif  // APP_H