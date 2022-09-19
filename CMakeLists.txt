cmake_minimum_required(VERSION 3.20.0)
project(Renderer)

# VCPKG
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_path(STB_INCLUDE_DIRS "stb_image.h")
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
# find_package(imgui CONFIG REQUIRED)
# find_package(implot CONFIG REQUIRED)

# MANUAL
set(IMGUI_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/deps/imgui")

file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.c*)

add_executable(renderer ${SOURCES})

target_link_libraries(renderer PRIVATE 
    glfw
    glad::glad
    glm::glm
    assimp::assimp
)
target_include_directories(renderer PRIVATE
    ${STB_INCLUDE_DIRS}
    ${IMGUI_INCLUDE_DIR}
)