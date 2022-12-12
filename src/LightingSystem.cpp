#include "LightingSystem.hpp"

// setters
void LightingSystem::setNewDirectionalLight(const std::string &name, DirectionalLight *newDirLight)
{
    DirLight.reset(newDirLight);
}
void LightingSystem::setNewPointLight(const std::string &name, PointLight *newPointLight)
{
    if (PointLightList.size() == 0 && pointLightModel == nullptr)
    {
        pointLightModel = new Model(FileSystem::getPath("models/lightbulb/scene.gltf"));
    }
    PointLightList.insert(std::pair(name, newPointLight));
}
void LightingSystem::setNewSpotLight(const std::string &name, SpotLight *newSpotLight)
{
    if (SpotLightList.size() == 0 && spotLightModel == nullptr)
    {
        spotLightModel = new Model(FileSystem::getPath("models/flashlight/scene.gltf"));
    }
    SpotLightList.insert(std::pair(name, newSpotLight));
}
// getters
DirectionalLight *LightingSystem::getDirectionalLight() { return DirLight.get(); }
PointLight *LightingSystem::getPointLight(std::string name) { return PointLightList.at(name).get(); }
SpotLight *LightingSystem::getSpotLight(std::string name) { return SpotLightList.at(name).get(); }

void LightingSystem::setupLighting(const Shader &shader)
{
    // Directional light
    if (DirLight != nullptr)
    {
        shader.setBool("hasDirLight", true);
        shader.setVec3("dirLight.direction", this->DirLight->getDirection());
        shader.setVec3("dirLight.ambient", this->DirLight->getAmbient());
        shader.setVec3("dirLight.diffuse", this->DirLight->getDiffuse());
        shader.setVec3("dirLight.specular", this->DirLight->getSpecular());
    }
    else
    {
        shader.setBool("hasDirLight", false);
    }

    // Point light
    if (PointLightList.size() > 0)
    {
        shader.setInt("NumberOfPointLight", PointLightList.size());
        int counter = 0;
        for (auto &pointLight : PointLightList)
        {
            shader.setVec3("pointLights[" + std::to_string(counter) + "].position", pointLight.second->getPosition());
            shader.setVec3("pointLights[" + std::to_string(counter) + "].ambient", pointLight.second->getAmbient());
            shader.setVec3("pointLights[" + std::to_string(counter) + "].diffuse", pointLight.second->getDiffuse());
            shader.setVec3("pointLights[" + std::to_string(counter) + "].specular", pointLight.second->getSpecular());
            shader.setFloat("pointLights[" + std::to_string(counter) + "].constant", pointLight.second->getConstant());
            shader.setFloat("pointLights[" + std::to_string(counter) + "].linear", pointLight.second->getLinear());
            shader.setFloat("pointLights[" + std::to_string(counter) + "].quadratic", pointLight.second->getQuadratic());
            counter++;
        }
    }
    else
    {
        shader.setInt("NumberOfPointLight", 0);
    }

    // To-do spot light
    // Spot light
    if (SpotLightList.size() > 0)
    {
        shader.setInt("NumberOfSpotLight", SpotLightList.size());
        int counter = 0;
        for (auto &spotLight : SpotLightList)
        {
            shader.setVec3("spotLights[" + std::to_string(counter) + "].position", spotLight.second->getPosition());
            shader.setVec3("spotLights[" + std::to_string(counter) + "].direction", spotLight.second->getDirection());
            shader.setVec3("spotLights[" + std::to_string(counter) + "].ambient", spotLight.second->getAmbient());
            shader.setVec3("spotLights[" + std::to_string(counter) + "].diffuse", spotLight.second->getDiffuse());
            shader.setVec3("spotLights[" + std::to_string(counter) + "].specular", spotLight.second->getSpecular());
            shader.setFloat("spotLights[" + std::to_string(counter) + "].constant", spotLight.second->getConstant());
            shader.setFloat("spotLights[" + std::to_string(counter) + "].linear", spotLight.second->getLinear());
            shader.setFloat("spotLights[" + std::to_string(counter) + "].quadratic", spotLight.second->getQuadratic());
            shader.setFloat("spotLights[" + std::to_string(counter) + "].cutOff", spotLight.second->getCutOff());
            shader.setFloat("spotLights[" + std::to_string(counter) + "].outerCutOff", spotLight.second->getOuterCutOff());
            counter++;
        }
    }
    else
    {
        shader.setInt("NumberOfSpotLight", 0);
    }
}

void LightingSystem::draw(Shader *pLightShader)
{
    if (PointLightList.size() > 0)
    {

        for (auto &pointLight : PointLightList)
        {
            pointLightModel->model = glm::mat4(1.0f);
            pointLightModel->model = glm::translate(pointLightModel->model, pointLight.second->getPosition());
            pointLightModel->model = glm::rotate(pointLightModel->model, glm::radians(-90.0f), glm::vec3(1.f, 0.f, 0.f));
            pointLightModel->model = glm::scale(pointLightModel->model, glm::vec3(1.0f));
            pointLightModel->draw(pLightShader);
        }
    }

    if (SpotLightList.size() > 0)
    {

        for (auto &spotLight : SpotLightList)
        {
            spotLightModel->model = glm::mat4(1.0f);
            spotLightModel->model = glm::translate(spotLightModel->model, spotLight.second->getPosition());

            float cosa = glm::dot(glm::normalize(glm::vec3(0.f, 0.f, 1.f)), glm::normalize(spotLight.second->getDirection()));
            glm::clamp(cosa, -1.0f, 1.0f);
            glm::vec3 axis = glm::cross(glm::normalize(glm::vec3(0.f, 0.f, 1.f)), glm::normalize(spotLight.second->getDirection()));
            float angle = glm::degrees(glm::acos(cosa));
            // std::cout << std::to_string(axis.x) + " " + std::to_string(axis.y) + " " + std::to_string(axis.z) + " " + std::to_string(angle) << std::endl;
            
            if (axis != glm::vec3(0.f))
                spotLightModel->model = glm::rotate(spotLightModel->model, glm::radians(angle), axis);
            else if (angle == 180.f)  
                spotLightModel->model = glm::rotate(spotLightModel->model, glm::radians(-angle), glm::vec3(0.f, 1.f, 0.f));
            spotLightModel->model = glm::scale(spotLightModel->model, glm::vec3(0.01f));
            spotLightModel->draw(pLightShader);
        }
    }
}
