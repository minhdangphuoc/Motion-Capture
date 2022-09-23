#include "App.hpp" 


App::App()
{
    glRenderrer.setCamera(new Camera(glm::vec3(0.0f, 0.0f, 3.0f)));
    
    
}

void App::init() 
{
    if(!window.GLFWInit())
    {
        glfwTerminate();
        throw "Failed to create GLFW window";
    }

    if(!window.controlInit())
    {
        throw "Failed to initialize controller";
    }

    if(!window.windowInit(&interface))
    {
        throw "Failed to create GLFW window";
    }

    if(!window.GLADInit())
    {
        throw "Failed to initialize GLAD";
    }

    if(glRenderrer.init() == EXIT_FAILURE)
    {
        throw "Failed to initialize GLRenderer";
    }
}

void App::run() 
{
    window.render(&glRenderrer, &interface);
}

void App::clean()
{
    interface.clean();
    window.clean();
}