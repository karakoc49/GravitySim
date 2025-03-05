# GravitySim

GravitySim is a cross-platform C++ application that simulates gravitational interactions between objects. It uses GLFW for window management and OpenGL for rendering.

## Features

- Simulates gravitational interactions between objects
- Cross-platform support (Windows, macOS, Linux)
- Uses GLFW for window management
- Uses OpenGL for rendering

## Requirements

- CMake 3.10 or higher
- A C++17 compatible compiler
- GLFW
- OpenGL

## Building the Project

1. **Clone the repository:**

    ```sh
    git clone https://github.com/yourusername/GravitySim.git
    cd GravitySim
    ```

2. **Create a build directory and navigate into it:**

    ```sh
    mkdir build
    cd build
    ```

3. **Run CMake to generate the build files:**

    ```sh
    cmake ..
    ```

4. **Build the project:**

   On Unix-like systems:

    ```sh
    make
    ```

   On Windows (using Visual Studio):

    ```sh
    cmake --build . --config Release
    ```

## Running the Application

After building the project, you can run the executable:

```sh
./GravitySim
```

On Windows, you can run the executable from the build directory:
```
GravitySim.exe
```