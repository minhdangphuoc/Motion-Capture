#define POLYGON_MODE 0

#include "Renderer.hpp"
#include "Utilities.h"

#include <iostream>
#include <stdexcept>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <array>


bool GLRenderer::init()
{
    try
    {
        initMaterial();
        loadShaders();
        loadFramebuffer();
        loadObjects();
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void GLRenderer::clean()
{   
    for (auto &it : Objects)
    {
        it.second->clean();
    }
}

bool GLRenderer::initMaterial()
{
    MaterialPresets.insert(std::pair("custom", Material(glm::vec3(0.0215f, 0.1745f, 0.0215f), glm::vec3(0.07568f, 0.61424f, 0.07568f), glm::vec3(0.633f, 0.727811f, 0.633f), 0.6f * 100.f)));
    MaterialPresets.insert(std::pair("emerald", Material(glm::vec3(0.0215f, 0.1745f, 0.0215f), glm::vec3(0.07568f, 0.61424f, 0.07568f), glm::vec3(0.633f, 0.727811f, 0.633f), 0.6f * 100.f)));
    MaterialPresets.insert(std::pair("jade", Material(glm::vec3(0.135f, 0.2225f, 0.1575f), glm::vec3(0.54f, 0.89f, 0.63f), glm::vec3(0.316228f, 0.316228f, 0.316228f), 0.1f * 100.f)));
    MaterialPresets.insert(std::pair("obsidian", Material(glm::vec3(0.05375f, 0.05f, 0.06625f), glm::vec3(0.18275f, 0.17f, 0.22525f), glm::vec3(0.332741f, 0.328634f, 0.346435f), 0.3f * 100.f)));
    MaterialPresets.insert(std::pair("pearl", Material(glm::vec3(0.25f, 0.20725f, 0.20725f), glm::vec3(1.0f, 0.829f, 0.829f), glm::vec3(0.296648f, 0.296648f, 0.296648f), 0.088f * 100.f)));
    MaterialPresets.insert(std::pair("ruby", Material(glm::vec3(0.1745f, 0.01175f, 0.01175f), glm::vec3(0.61424f, 0.04136f, 0.04136f), glm::vec3(0.727811f, 0.626959f, 0.626959f), 0.6f * 100.f)));
    MaterialPresets.insert(std::pair("turquoise", Material(glm::vec3(0.1f, 0.18725f, 0.1745f), glm::vec3(0.396f, 0.74151f, 0.69102f), glm::vec3(0.297254f, 0.30829f, 0.306678f), 0.1f * 100.f)));
    MaterialPresets.insert(std::pair("brass", Material(glm::vec3(0.329412f, 0.223529f, 0.027451f), glm::vec3(0.780392f, 0.568627f, 0.113725f), glm::vec3(0.992157f, 0.941176f, 0.807843f), 0.21794872f * 100.f)));
    MaterialPresets.insert(std::pair("bronze", Material(glm::vec3(0.2125f, 0.1275f, 0.054f), glm::vec3(0.714f, 0.4284f, 0.18144f), glm::vec3(0.393548f, 0.271906f, 0.166721f), 0.2f * 100.f)));
    MaterialPresets.insert(std::pair("chrome", Material(glm::vec3(0.25f, 0.25f, 0.25f), glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0.774597f, 0.774597f, 0.774597f), 0.6f * 100.f)));
    MaterialPresets.insert(std::pair("copper", Material(glm::vec3(0.19125f, 0.0735f, 0.0225f), glm::vec3(0.7038f, 0.27048f, 0.0828f), glm::vec3(0.256777f, 0.137622f, 0.086014f), 0.1f * 100.f)));
    MaterialPresets.insert(std::pair("gold", Material(glm::vec3(0.24725f, 0.1995f, 0.0745f), glm::vec3(0.75164f, 0.60648f, 0.22648f), glm::vec3(0.628281f, 0.555802f, 0.366065f), 0.4f * 100.f)));
    MaterialPresets.insert(std::pair("silver", Material(glm::vec3(0.19225f, 0.19225f, 0.19225f), glm::vec3(0.50754f, 0.50754f, 0.50754f), glm::vec3(0.508273f, 0.508273f, 0.508273f), 0.4f * 100.f)));
    MaterialPresets.insert(std::pair("black plastic", Material(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(0.5f, 0.5f, 0.5f), 0.25f * 100.f)));
    MaterialPresets.insert(std::pair("cyan plastic", Material(glm::vec3(0.0f, 0.1f, 0.06f), glm::vec3(0.0f, 0.50980392f, 0.50980392f), glm::vec3(0.50196078f, 0.50196078f, 0.50196078f), 0.25f * 100.f)));
    MaterialPresets.insert(std::pair("green plastic", Material(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.1f, 0.35f, 0.1f), glm::vec3(0.45f, 0.55f, 0.45f), 0.25f * 100.f)));
    MaterialPresets.insert(std::pair("red plastic", Material(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(0.7f, 0.6f, 0.6f), 0.25f * 100.f)));
    MaterialPresets.insert(std::pair("white plastic", Material(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.55f, 0.55f, 0.55f), glm::vec3(0.7f, 0.7f, 0.7f), 0.25f * 100.f)));
    MaterialPresets.insert(std::pair("yellow plastic", Material(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.6f, 0.6f, 0.5f), 0.25f * 100.f)));
    MaterialPresets.insert(std::pair("black rubber", Material(glm::vec3(0.02f, 0.02f, 0.02f), glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(0.4f, 0.4f, 0.4f), 0.078125f * 100.f)));
    MaterialPresets.insert(std::pair("cyan rubber", Material(glm::vec3(0.0f, 0.05f, 0.05f), glm::vec3(0.4f, 0.5f, 0.5f), glm::vec3(0.04f, 0.7f, 0.7f), 0.078125f * 100.f)));
    MaterialPresets.insert(std::pair("green rubber", Material(glm::vec3(0.0f, 0.05f, 0.0f), glm::vec3(0.4f, 0.5f, 0.4f), glm::vec3(0.04f, 0.7f, 0.04f), 0.078125f * 100.f)));
    MaterialPresets.insert(std::pair("red rubber", Material(glm::vec3(0.05f, 0.0f, 0.0f), glm::vec3(0.5f, 0.4f, 0.4f), glm::vec3(0.7f, 0.04f, 0.04f), 0.078125f * 100.f)));
    MaterialPresets.insert(std::pair("white rubber", Material(glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.7f, 0.7f, 0.7f), 0.078125f * 100.f)));
    MaterialPresets.insert(std::pair("yellow rubber", Material(glm::vec3(0.05f, 0.05f, 0.0f), glm::vec3(0.5f, 0.5f, 0.4f), glm::vec3(0.7f, 0.7f, 0.04f), 0.078125f * 100.f)));

    return true;
}

void GLRenderer::loadShaders()
{
    shaders.insert(std::pair("model", std::make_unique<Shader>(FileSystem::getPath("shaders/model.vert"), FileSystem::getPath("shaders/model.frag"))));
    shaders.insert(std::pair("lighting", std::make_unique<Shader>(FileSystem::getPath("shaders/light.vert"), FileSystem::getPath("shaders/light.frag"))));
    
}

void GLRenderer::loadObjects()
{
    glEnable(GL_DEPTH_TEST); // Z-Buffer
    Objects.insert(std::pair("Model1", std::make_unique<Model>(FileSystem::getPath("models/Sponza/glTF/Sponza.gltf"))));
    
    std::string str = FileSystem::getPath("models/TestAniModel/Standing Run Forward.dae");
    Objects.insert(std::pair("Model2", std::make_unique<Model>(str)));
    animation = new Animation(str, static_cast<Model *>(Objects.at("Model2").get()));
    animator = new Animator(animation);

    lightingSystem->setNewPointLight("PL1",
                                     new PointLight(
                                         glm::vec3(0.f, 5.f, 0.f),
                                         glm::vec3(0.0f, 0.5f, 0.0f),
                                         glm::vec3(0.f, 0.7f, 0.f),
                                         glm::vec3(0.5f, 0.5f, 0.5f),
                                         1.0f,
                                         0.14,
                                         0.07));
    lightingSystem->setNewPointLight("PL2",
                                     new PointLight(
                                         glm::vec3(-1.f, 1.f, 0.f),
                                         glm::vec3(0.0f, 0.f, 0.5f),
                                         glm::vec3(0.f, 0.f, 0.7f),
                                         glm::vec3(0.5f, 0.5f, 0.5f),
                                         1.0f,
                                         0.14,
                                         0.07));
    lightingSystem->setNewSpotLight("SL1", new SpotLight(
                                               glm::vec3(0.f, 3.f, 0.f),
                                               glm::vec3(0.f, -1.f, 0.f),
                                               glm::vec3(0.0f, 0.f, 0.f),
                                               glm::vec3(1.f),
                                               glm::vec3(1.f),
                                               1.0f,
                                               0.09,
                                               0.032,
                                               glm::cos(glm::radians(10.0f)),
                                               glm::cos(glm::radians(15.0f))));
}

void GLRenderer::loadFramebuffer() 
{
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    
    glViewport(0, 0, sWidth, sHeight);

    glGenTextures(1, &textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sWidth, sHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, sWidth, sHeight); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
}

void GLRenderer::setProjection()
{
    // glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)sWidth/ (float)sHeight , 0.1f, 100.0f);
    // shaders.at("shader")->setMat4("projection", projection);
}

void GLRenderer::setCamera(Camera * newCamera)
{
    camera.reset(newCamera);
}


void GLRenderer::draw() 
{
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glEnable(GL_DEPTH_TEST); // Z-Buffer

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    animator->UpdateAnimation(deltaTime);
    
    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)sWidth/ (float)sHeight , 0.1f, 100.0f);
    glm::mat4 view = camera->GetViewMatrix();

    shaders.at("model")->use();
    shaders.at("model")->setVec3("viewPos", camera->Position);

    shaders.at("model")->setMat4("projection", projection);
    shaders.at("model")->setMat4("view", view);

    // SPONZA
    Objects.at("Model1")->model = glm::mat4(1.0f);
    Objects.at("Model1")->model = glm::translate(Objects.at("Model1")->model, glm::vec3(0.0f, 0.0f, .175f)); // translate it down so it's at the center of the scene
    Objects.at("Model1")->model = glm::scale(Objects.at("Model1")->model, glm::vec3(0.005f));

    // light
    lightingSystem->setupLighting(*(shaders.at("model").get()));

    Objects.at("Model1")->draw(shaders.at("model").get());

    // ANIModel
    shaders.at("model")->use();
    shaders.at("model")->setVec3("viewPos", camera->Position);
    shaders.at("model")->setMat4("projection", projection);
    shaders.at("model")->setMat4("view", view);

    Objects.at("Model2")->model = glm::mat4(1.0f);
    Objects.at("Model2")->model = glm::rotate(Objects.at("Model2")->model, glm::radians(90.0f), glm::vec3(0.f, 1.f, 0.f));
    Objects.at("Model2")->model = glm::scale(Objects.at("Model2")->model, glm::vec3(0.7f));

    auto transforms = animator->GetFinalBoneMatrices();

    for (int i = 0; i < transforms.size(); ++i)
    {
        shaders.at("model")->setMat4("finalBonesMatrices[" + std::to_string(i) + "]", Objects.at("Model2")->model * transforms[i]);
    }

    // light
    lightingSystem->setupLighting(*(shaders.at("model").get()));

    Objects.at("Model2")->draw(shaders.at("model").get());

    shaders.at("lighting")->use();
    shaders.at("lighting")->setMat4("projection", projection);
    shaders.at("lighting")->setMat4("view", view);

    lightingSystem->draw(shaders.at("lighting").get());
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT);
}