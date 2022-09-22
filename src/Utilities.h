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

#endif // __UTILITIES_H__