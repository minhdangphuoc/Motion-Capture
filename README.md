# OpenGL ES Renderer

[[_TOC_]]

## Version

- [0.0.1] Basic triangle
- [0.0.2] Depth Buffer and Camera system
- [0.0.3] getPath system and Camera Class
- [0.0.4] Imgui implement

## Pre-develop setups

- Install vcpkg, OpenGL, Assimp, GLFW, GLM, GLAD, STB, Imgui, Cmake.
- Setup Gitlab CI

### vcpkg

```

    git clone https://github.com/Microsoft/vcpkg.git
    ./vcpkg/bootstrap-vcpkg.sh
    vcpkg install assimp glfw3 glm glad stb imgui implot

```

## Build

```

    mkdir build && cd build && cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake && cmake --build build

```