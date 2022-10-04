#include "Interface.hpp"
#include <iostream>

void Interface::init(const std::string & glsl_version, GLFWwindow * window)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    // Setup Dear ImGui style
    ImGui::Spectrum::StyleColorsSpectrum();
    
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 8.0f);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.2f, 0.2f, 0.2f, 0.8f));

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    io.ConfigInputTrickleEventQueue = false;
    ImGui_ImplOpenGL3_Init(glsl_version.c_str());
}

void Interface::start()
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame(); 
}

void Interface::render()
{
    ImGui::Render();
}

void Interface::renderDrawData()
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Interface::clean()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();
}

void Interface::beginWindow(std::string wName, bool & isActivate)
{
    if (isActivate)
    ImGui::Begin(wName.c_str(), &isActivate);
}

void Interface::beginWindow(std::string wName)
{
    ImGui::Begin(wName.c_str());
}

void Interface::endWindow()
{
    ImGui::End();
}

void Interface::createText(std::string title)
{  
    ImGui::Text(title.c_str());
}

void Interface::createColorText(ImVec4 color,std::string title)
{
    ImGui::TextColored(color, title.c_str());
}

void Interface::createFloatSlider(std::string title, float &f, const float min, const float max)
{
    ImGui::SliderFloat(title.c_str(), &f, min, max);
}

void Interface::createIntSlider(std::string title, int& f, const int min, const int max)
{
    ImGui::SliderInt(title.c_str(), &f, min, max);
}

void Interface::createPlotLine(std::string title, std::vector<float> & x_data, std::vector<float> & y_data, int size)
{
    ImPlot::BeginPlot("FPS Line Chart", ImVec2(320.f, 160.f), ImPlotFlags_NoTitle);
    ImPlot::SetupAxis(ImAxis_X1, "", ImPlotAxisFlags_AutoFit + ImPlotAxisFlags_NoTickLabels);
    ImPlot::SetupAxis(ImAxis_Y1, "", ImPlotAxisFlags_AutoFit);
    ImPlot::SetupFinish();
    ImPlot::PlotLine(title.c_str(), x_data.data(), y_data.data(), size);
    ImPlot::EndPlot();
}

void Interface::createPlotBar(std::string title, std::vector<float>& bar_data, int size)
{
    ImPlot::BeginPlot(title.c_str(), ImVec2(320.f, 160.f), ImPlotFlags_NoTitle);
    ImPlot::SetupAxis(ImAxis_X1, "", ImPlotAxisFlags_AutoFit + ImPlotAxisFlags_NoTickLabels);
    ImPlot::SetupAxis(ImAxis_Y1, "", ImPlotAxisFlags_AutoFit);
    ImPlot::SetupFinish();
    ImPlot::PlotBars(title.c_str(), bar_data.data(), size);
    ImPlot::EndPlot();
}

void Interface::createColorEdit3(const std::string title, float*  color)
{
    ImGui::ColorEdit3(title.c_str(), color);
}

void Interface::createColorEdit4(const std::string title, float* color)
{
    ImGui::ColorEdit4(title.c_str(), color);
}

void Interface::createButton(const std::string title)
{
    ImGui::Button(title.c_str());
}

void Interface::createCheckbox(const std::string title, bool* value)
{
    ImGui::Checkbox(title.c_str(), value);

}

void Interface::createInputTextBox(const std::string title,char* buf, size_t buf_size)
{
    ImGui::InputText(title.c_str(), buf, buf_size);
}

void Interface::createMultilineInputTextBox(const std::string title, char* buf, size_t buf_size)
{
    ImGui::InputTextMultiline(title.c_str(), buf, buf_size);
}


void Interface::createMenuBar()
{
    ImGui::BeginMenuBar();
}

void Interface::createMenu(const std::string title)
{
    ImGui::BeginMenu(title.c_str());
}

void Interface::addMenuItem(const std::string item, bool* showItem)
{
    ImGui::MenuItem(item.c_str(), NULL, &showItem);
}

void Interface::endMenu()
{
    ImGui::EndMenu();
}

void Interface::endMenuBar()
{
    ImGui::EndMenuBar();
}

void Interface::createImageView(const std::string & title, const uint32_t & buffer, uint32_t * width, uint32_t * height)
{   
    ImGui::BeginChild(title.c_str());
    *width = ImGui::GetWindowSize().x;
    *height = ImGui::GetWindowSize().y;
    ImGui::Image((ImTextureID)buffer, ImVec2(*width, *height), ImVec2(0, 1), ImVec2(1, 0));
    ImGui::EndChild();
}