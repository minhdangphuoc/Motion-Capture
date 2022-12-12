#pragma once
#ifndef MODEL_HPP
#define MODEL_HPP

#include <cstdint> 
#include <vector>
#include <string>
#include <map>
#include <cstdint> 
#include <glm/gtc/matrix_transform.hpp>

#include "Mesh.hpp"
#include "Shader.hpp"
#include "Material.hpp"
#include "Object.hpp"
#include "Texture.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>




class Model: public Object
{
public:

    Model(std::string path)
    {
        this->model = glm::mat4(1.0f);
        loadModel(path);
    }
    void draw(Shader *shader);	
    void setMaterial(const Material & newMaterial) {}
    // model data 
    std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh>    meshes;
    std::string directory;
    bool gammaCorrection;

    void clean();

private:


    void loadModel(std::string const &path);
    Material loadMaterial(aiMaterial* mat);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
                                             std::string typeName);
    uint32_t TextureFromFile(const char *path, const std::string &directory, bool gamma);

};

#endif // MODEL_HPP