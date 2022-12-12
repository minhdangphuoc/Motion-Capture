#pragma once
#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace FileSystem {
#include <string>
    static std::string getPath(const std::string & raw)
    {
        #if defined(_WIN64) || defined(_WIN32) 
            return "./resources/" + raw;
        #elif defined(__linux__) || defined(__APPLE__)
            return "./resources/" + raw;
        #endif
    }
};

static std::string readFile(const std::string& path) {
	std::string sourceCode;
    std::ifstream file;

	file.exceptions (std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		file.open(path);
		std::stringstream fileStream;
		fileStream << file.rdbuf();
		file.close();
		sourceCode = fileStream.str();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return sourceCode;
}

static glm::vec3 vec3_cast(const aiVector3D &v) { return glm::vec3(v.x, v.y, v.z); }
static glm::vec2 vec2_cast(const aiVector3D &v) { return glm::vec2(v.x, v.y); }
static glm::quat quat_cast(const aiQuaternion &q) { return glm::quat(q.w, q.x, q.y, q.z); }
static glm::mat4 mat4_cast(const aiMatrix4x4 &m) { return glm::transpose(glm::make_mat4(&m.a1)); }
static glm::mat4 mat4_cast(const aiMatrix3x3 &m) { return glm::transpose(glm::make_mat3(&m.a1)); }
static glm::vec3 mid_point_vec3(const glm::vec3 &v1, const glm::vec3 &v2)
{
	return glm::vec3((v1.x + v2.x) / 2, (v1.y + v2.y) / 2, (v1.z + v2.z) / 2);
}
static std::string printVec3(const glm::vec3 &v3) { return std::to_string(v3.x) + "," + std::to_string(v3.y) + "," + std::to_string(v3.z); }

#endif // __UTILITIES_H__