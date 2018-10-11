#include <iostream>
#include "app.h"

int main(int argc, char** argv)
{
    App app("Assignment 1", 1080, 720, &argc, argv);
    app.run();

    return 0;
}