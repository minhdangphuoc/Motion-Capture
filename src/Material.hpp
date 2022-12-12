#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>
#include <vector>
#include <string>

const std::vector<std::string> MaterialNames = {
    "none",
    "emerald",
    "jade",
    "obsidian",
    "pearl",
    "ruby",
    "turquoise",
    "brass",
    "bronze",
    "chrome",
    "copper",
    "gold",
    "silver",
    "black plastic",
    "cyan plastic",
    "green plastic",
    "red plastic",
    "white plastic",
    "yellow plastic",
    "black rubber",
    "cyan rubber",
    "green rubber",
    "red rubber",
    "white rubber",
    "yellow rubber",
};


class Material {
    public:
    Material()=default;
    Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess): Ambient(ambient), Diffuse(diffuse), Specular(specular), Shininess(shininess){};
    glm::vec3 Diffuse;
    glm::vec3 Specular;
    glm::vec3 Ambient;
    float Shininess = 2.f;
    bool operator!= (const Material & mt)
    {
        return !((this -> Ambient == mt.Ambient)&&(this -> Diffuse == mt.Diffuse)&&(this -> Specular == mt.Specular)&&(this -> Shininess == mt.Shininess));
    }
};

#endif // !MATERIAL_H