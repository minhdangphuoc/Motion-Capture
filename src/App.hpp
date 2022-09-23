#ifndef APP_HPP
#define APP_HPP

#include "window.hpp"
#include "Interface.hpp"

class App 
{
    public:
    App();
    ~App() = default;

    void init();
    void run();
    void clean();

    private:
    Window window;
    GLRenderer glRenderrer;
    Interface interface;
};

#endif // !APP_HPP
