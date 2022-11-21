#pragma once
#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include "Vertex.hpp"
#include "Texture.hpp" 
#include "Shader.hpp"

class Mesh {
    public:
        Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<Texture> textures);
        ~Mesh() = default;

        void draw(Shader *shader);

        // mesh data
        std::vector<Vertex>       vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture>      textures;

        void cleanData();
    private:
        //  render data
        uint32_t VAO, VBO, EBO;
        void setupMesh();

};  

#endif // !MESH_HPP