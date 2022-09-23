#pragma once
#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__

#include <iostream>
#include <cstdint> 
#include <glad/glad.h> 
#include <string>

class Texture
{
private:
    uint32_t texture;
public:
    Texture(std::string path);
    ~Texture() = default;

    uint32_t getTexture() {return texture;}
};

#endif // __TEXTURE_HPP__