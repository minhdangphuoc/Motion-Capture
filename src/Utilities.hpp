#ifndef UTILITIES_HPP
#define UTILITIES_HPP

namespace FileSystem {
#include <string>
    std::string getPath(const std::string & raw)
    {
        #if defined(_WIN64) || defined(_WIN32) 
            return "../../" + raw;
        #elif defined(__linux__) || defined(__APPLE__)
            return "../" + raw;
        #endif
    }
};

#endif // !UTILITIES_HPP