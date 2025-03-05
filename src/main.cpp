#include <iostream>
#include <GLFW/glfw3.h>
#include <vector>

#include "renderer.h"
#include "constants.h"

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main() {
    // Initialize GLFW
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(Config::SCR_WIDTH, Config::SCR_HEIGHT, "Gravity Sim", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Enable 2D projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspectRatio = (float)Config::SCR_WIDTH / (float)Config::SCR_HEIGHT;
    glOrtho(-aspectRatio, aspectRatio, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    // Create objects
    std::vector<Circle> circles = {
        Circle(1, 0.0f, 0.0f, 0.1f, 100, 9000000.0f, {1.0f, 0.0f, 0.0f}),
        Circle(2, -0.5f, 0.5f, 0.05f, 100, 1000000.0f, {0.0f, 1.0f, 0.0f}),
        Circle(3, 0.5f, 0.5f, 0.05f, 100, 5000000.0f, {0.0f, 0.0f, 1.0f}),
    };

    Renderer renderer;

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        std::cout << "\r";

        for (Circle& circle : circles) {
            circle.applyGravity(circles);
            circle.update(deltaTime);

            for (auto& other : circles) {
                if (&circle != &other) { // Avoid self-collision
                    circle.resolveCollision(other);
                }
            }

            // Print circle attributes
            circle.printAttributes();
        }

        renderer.render(circles); // Draw circles

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
