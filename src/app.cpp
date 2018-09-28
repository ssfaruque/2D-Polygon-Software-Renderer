#include <GL/freeglut.h>

#include "app.h"


App::App(int* argc, char** argv):
m_running(true)
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
}