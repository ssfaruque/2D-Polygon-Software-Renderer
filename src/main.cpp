#include <iostream>
#include "app.h"

int main(int argc, char** argv)
{
    App::create("Assignment 1", 1080, 720, &argc, argv);
    App* app = App::getInstance();
    app->run();

    return 0;
}