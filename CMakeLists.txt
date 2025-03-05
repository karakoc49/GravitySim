cmake_minimum_required(VERSION 3.10)

# Set the project name
project(GravitySim)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(GravitySim
    src/main.cpp
    src/circle.cpp
    src/renderer.cpp
    src/constants.h
    src/circle.h
    src/renderer.h
)

# Set the GLFW include and library directories
set(GLFW_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(GLFW_LIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")

# Include GLFW headers
include_directories(${GLFW_INCLUDE_DIR})

# Link GLFW library
find_library(GLFW_LIBRARY glfw3 HINTS ${GLFW_LIBRARY_DIR})
target_link_libraries(GravitySim PRIVATE ${GLFW_LIBRARY})

# Find and link OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(GravitySim PRIVATE OpenGL::GL)

# Include directories
target_include_directories(GravitySim PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)