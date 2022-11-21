#pragma once
#ifndef __Controller_hpp__
#define __Controller_hpp__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "CameraSystem.hpp"


class Controller
{
public:
    Controller() = default;
    ~Controller() = default;

    // static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    bool firstMouse = true;
    float lastX;
    float lastY;
    private:
};

#endif //__Controller_hpp__