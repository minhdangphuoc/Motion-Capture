#include <cstdint> 
#include <vector>

class Object
{
public:
    Object(std::vector<float>  vertices, std::vector<uint32_t> indices): vertices(vertices), indices(indices){};
    Object(std::vector<float>  vertices) : vertices(vertices) {};
    
    ~Object() {};
    uint32_t VBO, VAO, EBO;
    std::vector<float> vertices;
    std::vector<uint32_t> indices;

    // getters
    
private:

};