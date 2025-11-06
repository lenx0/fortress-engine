cmake_minimum_required(VERSION 3.16)
project(GameEngine)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Application.cpp
    src/Window.cpp
    src/Renderer.cpp
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Find OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)

# For Windows, we'll use vcpkg to manage GLFW, GLAD and GLM
if(WIN32)
    find_package(glfw3 CONFIG REQUIRED)
    find_package(glad CONFIG REQUIRED)
    find_package(glm CONFIG REQUIRED)
    target_link_libraries(${PROJECT_NAME} glfw glad::glad glm::glm)
endif()

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Copy shaders to output directory
file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR}/bin)