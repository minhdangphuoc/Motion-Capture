#pragma once
#ifndef __INTERFACE_HPP__
#define __INTERFACE_HPP__

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_spectrum.h>

#include <implot.h>
#include <implot_internal.h>
#include "glm/glm.hpp"

#include <string>
#include <memory>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <array>
#include <vector>
class Interface
{
private:
    
public:
    // Con/Destructor
    Interface() = default;
    ~Interface() = default; 

    void init(const std::string & glsl_version, GLFWwindow * window);
    void render();
    void renderDrawData();
    void clean();
    void start();

    void beginWindow(std::string wName, bool & isActivate);
    void beginWindow(std::string wName);

    void endWindow();

    // Component
    void createText(std::string title);
    void createColorText(ImVec4 color, std::string title);
    void createFloatSlider(std::string title, float &f, const float min, const float max);
    void createIntSlider(std::string title, int &f, const int min, const int max);
    void createPlotLine(std::string title, std::vector<float> & x_data, std::vector<float> & y_data, int size);
    void createPlotBar(std::string title, std::vector<float>& bar_data, int size);
    void createColorEdit3(std::string title, float * color);
    void createColorEdit4(std::string title, float * color);
    void createButton(std::string title);
    void createCheckbox(std::string label, bool* value);
    void createInputTextBox(std::string label,char* buf, size_t buf_size);
    void createMultilineInputTextBox(std::string label, char* buf, size_t buf_size);
    void drawImage(uint32_t texture, float width, float height);

    void createImageView(const std::string & title, const uint32_t & buffer, uint32_t * width, uint32_t * height);

    void createMenuBar();
    void createMenu(std::string title);
    void addMenuItem(std::string title, bool* showItem);
    void endMenu();
    void endMenuBar();
    
};

#endif // __INTERFACE_HPP__