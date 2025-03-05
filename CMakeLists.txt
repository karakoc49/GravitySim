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

# Check the operating system
if(WIN32)
    # For Windows: Use the local GLFW library
    set(GLFW_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
    set(GLFW_LIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")

    # Include GLFW headers
    include_directories(${GLFW_INCLUDE_DIR})

    # Link GLFW library
    find_library(GLFW_LIBRARY glfw3 HINTS ${GLFW_LIBRARY_DIR})
    target_link_libraries(GravitySim PRIVATE ${GLFW_LIBRARY})

elseif(APPLE)
    # For macOS: Link against the OpenGL framework and GLFW
    find_package(glfw3 REQUIRED)
    target_link_libraries(GravitySim PRIVATE glfw)

    # Link OpenGL on macOS (macOS uses its own OpenGL framework)
    target_link_libraries(GravitySim PRIVATE "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreFoundation")

else()
    # For Linux (or other UNIX-like systems): Use the system-wide GLFW
    find_package(glfw3 REQUIRED)
    target_link_libraries(GravitySim PRIVATE glfw)
    
    # Link OpenGL on Linux (using OpenGL package)
    find_package(OpenGL REQUIRED)
    target_link_libraries(GravitySim PRIVATE OpenGL::GL)
endif()

# Include directories for your source files
target_include_directories(GravitySim PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

