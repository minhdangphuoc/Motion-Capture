#define TRANSPARENCY_MODE MODE_OFF
#define VSYNC_MODE MODE_ON

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.hpp"

bool Window::init() 
{
    try {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
        #if (VSYNC_MODE)
            std::cout<< "VSYNC on" << std::endl;
            glfwSwapInterval(1);
        #else
            glfwSwapInterval(0);
        #endif
        
        #if (TRANSPARENCY_MODE)
            glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
        #endif
        
        #ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif
    } 
    catch (const std::exception & err) 
    {
        std::cout << err.what() << std::endl;
    }

    return true;
}