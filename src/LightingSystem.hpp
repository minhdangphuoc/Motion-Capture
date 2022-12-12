#pragma once
#ifndef LIGHTING_SYSTEM
#define LIGHTING_SYSTEM

#include "Object.hpp"
#include "glm/glm.hpp"
#include "glm/gtx/euler_angles.hpp"
#include <glm/gtx/rotate_vector.hpp>
#include "Shader.hpp"
#include "Model.hpp"

#include <unordered_map>
#include <string>
#include <memory>

class Lighting : public Object
{
public:
    Lighting() = default;
    ~Lighting() = default;
    void clean(){}
    void draw(Shader *shader){}
    void renderInterface(){}
    void setMaterial(const Material & newaterial){}
protected:
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

class DirectionalLight : public Lighting
{
public:
    DirectionalLight(
        const glm::vec3 &direction = glm::vec3(0.f),
        const glm::vec3 &ambient = glm::vec3(0.f),
        const glm::vec3 &diffuse = glm::vec3(0.f),
        const glm::vec3 &specular = glm::vec3(0.f))
    {
        this->direction = direction;
        this->ambient = ambient;
        this->diffuse = diffuse;
        this->specular = specular;
    }

    // setters
    void setDirection(glm::vec3 newDir) { this->direction = newDir; }
    void setAmbient(glm::vec3 ambient) { this->ambient = ambient; }
    void setDiffuse(glm::vec3 diffuse) { this->diffuse = diffuse; }
    void setSpecular(glm::vec3 specular) { this->specular = specular; }

    // getter
    glm::vec3 getDirection() { return this->direction; }
    glm::vec3 getAmbient() { return this->ambient; }
    glm::vec3 getDiffuse() { return this->diffuse; }
    glm::vec3 getSpecular() { return this->specular; }

};

class PointLight : public Lighting
{
public:
    PointLight(
        const glm::vec3 &position = glm::vec3(0.f),
        const glm::vec3 &ambient = glm::vec3(0.f),
        const glm::vec3 &diffuse = glm::vec3(0.f),
        const glm::vec3 &specular = glm::vec3(0.f),
        const float &constant = 0.f,
        const float &linear = 0.f,
        const float &quadratic = 0.f)
    {
        this->position = position;
        this->ambient = ambient;
        this->diffuse = diffuse;
        this->specular = specular;
        this->constant = constant;
        this->linear = linear;
        this->quadratic = quadratic;
    }

    // setters
    void setPosition(glm::vec3 newPos) { this->position = newPos; }
    void setAmbient(glm::vec3 newAmbient) { this->ambient = newAmbient; }
    void setDiffuse(glm::vec3 newDiffuse) { this->diffuse = newDiffuse; }
    void setSpecular(glm::vec3 newSpecular) { this->specular = newSpecular; }
    void setConstant(float newConstant) { this->constant = newConstant; }
    void setLinear(float newLinear) { this->linear = newLinear; }
    void setQuadratic(float newQuadratic) { this->quadratic = newQuadratic; }

    // getter
    glm::vec3 getPosition() { return this->position; }
    glm::vec3 getAmbient() { return this->ambient; }
    glm::vec3 getDiffuse() { return this->diffuse; }
    glm::vec3 getSpecular() { return this->specular; }
    float getConstant() { return this->constant; }
    float getLinear() { return this->linear; }
    float getQuadratic() { return this->quadratic; }


private:
    // Unique attributes
    float constant;
    float linear;
    float quadratic;
};

class SpotLight : public Lighting
{
public:
    SpotLight(
        const glm::vec3 &position = glm::vec3(0.f),
        const glm::vec3 &direction = glm::vec3(0.f),
        const glm::vec3 &ambient = glm::vec3(0.f),
        const glm::vec3 &diffuse = glm::vec3(0.f),
        const glm::vec3 &specular = glm::vec3(0.f),
        const float &constant = 0.f,
        const float &linear = 0.f,
        const float &quadratic = 0.f,
        const float &cutOff = 0.f,
        const float &outerCutOff = 0.f)
    {
        this->position = position;
        this->direction = direction;
        this->ambient = ambient;
        this->diffuse = diffuse;
        this->specular = specular;
        this->constant = constant;
        this->linear = linear;
        this->quadratic = quadratic;
        this->cutOff = cutOff;
        this->outerCutOff = outerCutOff;
    }

    // setters
    void setPosition(glm::vec3 newPos) { this->position = newPos; }
    void setDirection(glm::vec3 newDir) { this->direction = newDir; }
    void setAmbient(glm::vec3 newAmbient) { this->ambient = newAmbient; }
    void setDiffuse(glm::vec3 newDiffuse) { this->diffuse = newDiffuse; }
    void setSpecular(glm::vec3 newSpecular) { this->specular = newSpecular; }
    void setCutOff(float newCutOff) { this->cutOff = newCutOff; }
    void setOuterCutOff(float newOuterCutOff) { this->outerCutOff = newOuterCutOff; }
    void setConstant(float newConstant) { this->constant = newConstant; }
    void setLinear(float newLinear) { this->linear = newLinear; }
    void setQuadratic(float newQuadratic) { this->quadratic = newQuadratic; }

    // getter
    glm::vec3 getPosition() { return this->position; }
    glm::vec3 getDirection() { return this->direction; }
    glm::vec3 getAmbient() { return this->ambient; }
    glm::vec3 getDiffuse() { return this->diffuse; }
    glm::vec3 getSpecular() { return this->specular; }
    float getCutOff() { return this->cutOff; }
    float getOuterCutOff() { return this->outerCutOff; }
    float getConstant() { return this->constant; }
    float getLinear() { return this->linear; }
    float getQuadratic() { return this->quadratic; }
    
private:
    // Unique attributes
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;
};

class LightingSystem
{
public:
    void setupLighting(const Shader &shader);
    void draw(Shader *);

    // setters
    void setNewDirectionalLight(const std::string &name, DirectionalLight *newDirLight);
    void setNewPointLight(const std::string &name, PointLight *newPointLight);
    void setNewSpotLight(const std::string &name, SpotLight *newSpotLight);
    // getters
    DirectionalLight *getDirectionalLight();
    PointLight *getPointLight(std::string name);
    SpotLight *getSpotLight(std::string name);

private:
    static inline Object *pointLightModel;
    static inline Object *spotLightModel;
    
    std::unique_ptr<DirectionalLight> DirLight;
    std::unordered_map<std::string, std::unique_ptr<PointLight>> PointLightList;
    std::unordered_map<std::string, std::unique_ptr<SpotLight>> SpotLightList;
};

#endif // !LIGHTING_SYSTEM