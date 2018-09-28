#include <GL/freeglut.h>

#include "app.h"
#include "window.h"


App::App(int* argc, char** argv):
m_running(true)
{
    glutInit(argc, argv);
}