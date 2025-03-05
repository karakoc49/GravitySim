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

2. **Install dependencies:**
    - On **Debian-based systems** (e.g., Ubuntu, Linux Mint), install the required libraries using the following command:

    ```sh
    sudo apt update
    sudo apt install libglfw3 libglfw3-dev
    ```
    - On **Arch-based systems** (e.g., Arch Linux, Manjaro), install the required libraries using:

    ```sh
    sudo pacman -S glfw-x11 mesa
    ```
    - On **macOS**, you can install the dependencies using **Homebrew**. If you don't have Homebrew installed, you can install it by following the instructions [here](https://brew.sh). Then, run:

    ```sh
    brew install glfw
    ```
3. **Create a build directory and navigate into it:**

    ```sh
    mkdir build
    cd build
    ```

4. **Run CMake to generate the build files:**

    ```sh
    cmake ..
    ```

5. **Build the project:**

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
