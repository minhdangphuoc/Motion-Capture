#pragma once
#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__


#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>


#include "Interface.hpp"
#include "Controller.hpp"
#include "Renderer.hpp"

class Window
{
public:
    Window() = default;
    ~Window() = default;

    
    // Renderer Functions
    
    bool GLFWInit();
    bool GLADInit();
    bool windowInit(Interface *interface);
    bool controlInit();
    void render(GLRenderer *program, Interface *interface);
    void clean();

    // Setters
    void setCamera(Camera * newCamera);
private:
    uint32_t frameCount = 0;
    void processInput(GLRenderer * renderer);
    struct glfwDeleter
    {
        void operator()(GLFWwindow *window)
        {
            std::cout << "Destroying GLFW Window Context" << std::endl;
            glfwDestroyWindow(window);
            std::cout << "Destroyed GLFW Window Context" << std::endl;
        }
    };

    struct rendererDeleter
    {
        void operator()(GLRenderer *renderer)
        {
            std::cout << "Destroying renderer" << std::endl;
            renderer -> clean();
            std::cout << "Destroyed renderer" << std::endl;
        }    
    };
    std::unique_ptr<GLFWwindow, glfwDeleter> window;
    // std::unique_ptr<GLRenderer, rendererDeleter> renderer;
    std::unique_ptr<Controller> HWInput;
    
    bool isPressAlt = false;
};

#endif // __WINDOW_HPP__