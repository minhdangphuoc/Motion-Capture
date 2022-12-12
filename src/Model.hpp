#pragma once
#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

#include <cstdint> 
#include <vector>
#include <string>
#include <map>
#include <cstdint> 

#include "Utilities.h"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Material.hpp"
#include "Object.hpp"
#include "BoneInfo.hpp"

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
    void clean();
    
    // model data 
    std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh>    meshes;
    std::string directory;
    bool gammaCorrection;
    auto& GetBoneInfoMap() { return m_BoneInfoMap; }
    int& GetBoneCount() { return m_BoneCounter; }

private:
    // Vars
    uint32_t TextureFromFile(const char *path, const std::string &directory, bool gamma);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
                                             std::string typeName);

    std::map<std::string, BoneInfo> m_BoneInfoMap; 
    int m_BoneCounter = 0;
    bool hasAnimated = false;


    // Function
    void loadModel(std::string const &path);
    Material loadMaterial(aiMaterial* mat);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    void SetVertexBoneDataToDefault(Vertex& vertex);
    void SetVertexBoneData(Vertex& vertex, int boneID, float weight);
    void ExtractBoneWeightForVertices(std::vector<Vertex>& vertices, aiMesh* mesh, const aiScene* scene);

    
};

#endif