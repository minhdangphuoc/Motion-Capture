
#include <iostream>

#include "App.hpp"

int main(int argc, const char** argv) 
{
    App app;
    try
    {
        app.init();
    }
    catch (const std::runtime_error& err)
    {
        std::cerr << err.what() << std::endl;
        return EXIT_FAILURE;
    }
    app.run();

    app.clean();
    return 0;
}
