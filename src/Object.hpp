#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Material.hpp"
#include "Shader.hpp"
// Object interface
class Object 
{
public:
    Object() = default;
    ~Object() = default;
    virtual void draw(Shader *shader) = 0;
    virtual void clean() = 0;
    virtual void setMaterial(const Material & newaterial) = 0;
    unsigned int selectedMaterial = 0;
    glm::mat4 model; // Remove this in future -> init and deleted when drawing object
protected:
    
};

#endif // !OBJECT_HPP