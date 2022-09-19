cmake_minimum_required(VERSION 3.20.0)
project(Renderer)

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_path(STB_INCLUDE_DIRS "stb_image.h")
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(main src/main.cpp "src/Shader.h" "src/stb_image.h")

target_link_libraries(main PRIVATE 
    glfw
    glad::glad
    glm::glm
    assimp::assimp
)
target_include_directories(main PRIVATE
    ${STB_INCLUDE_DIRS}
)