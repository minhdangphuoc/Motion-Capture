# OpenGL ES Renderer

[[TOC]]
## Pre-develop setups

- Install vcpkg, OpenGL, Assimp, GLFW, GLM, GLAD, STB, Imgui, Cmake.
- Setup Gitlab CI

### vcpkg

'''
    git clone https://github.com/Microsoft/vcpkg.git
    ./vcpkg/bootstrap-vcpkg.sh
    vcpkg install assimp glfw glm glad stb imgui implot
'''

## Build

''' 
    mkdir build && cd build && cmake .. && 
'''