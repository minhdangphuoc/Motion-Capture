#pragma once
#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>
#include <cstdint> 
#include <glad/glad.h> 
#include <string>

class Texture
{
private:
public:
    uint32_t id;
    std::string type;
    std::string path;

    uint32_t getTexture() {return id;}
};

#endif // __TEXTURE_HPP__