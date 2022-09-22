cmake_minimum_required(VERSION 3.20.0)

set(APP_NAME GLRenderer)
project(${APP_NAME} VERSION 0.0.3)

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
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.c*)
add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# COPY RESOURCE FILES
file( COPY ${PROJECT_SOURCE_DIR}/resources 
    DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}" )
file( COPY "${PROJECT_SOURCE_DIR}/imgui.ini"
    DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}" )
    
target_link_libraries(${PROJECT_NAME} PRIVATE 
    glfw
    glad::glad
    glm::glm
    assimp::assimp
)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${STB_INCLUDE_DIRS}
    ${IMGUI_INCLUDE_DIR}
)
