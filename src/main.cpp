#include <iostream>
#include "app.h"

int main(int argc, char** argv)
{
    App app("assignment 1", 1080, 720, &argc, argv);
    app.run();

    return EXIT_SUCCESS;
}