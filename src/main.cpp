#include <iostream>
#include <GLFW/glfw3.h>
#include <vector>

#include "renderer.h"
#include "constants.h"

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void processInput(GLFWwindow* window, std::vector<Circle>* circles);

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
        Circle(1, 0.0f, 0.0f, 0.1f, 100, 100.0f, {1.0f, 0.0f, 0.0f}),
        Circle(2, -0.5f, 0.5f, 0.05f, 100, 10.0f, {0.0f, 1.0f, 0.0f}),
        Circle(3, 0.5f, 0.5f, 0.05f, 100, 1.0f, {0.0f, 0.0f, 1.0f}),
    };

    Renderer renderer;

    while (!glfwWindowShouldClose(window)) {
        processInput(window, &circles);
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

// handle controls
void processInput(GLFWwindow* window, std::vector<Circle>* circles) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    // create a new circle on mouse right click at the cursor position. create only one circle per click
    static bool isPressed = false;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        if (!isPressed) {
            double x, y;
            glfwGetCursorPos(window, &x, &y);
            x = (x / Config::SCR_WIDTH) * 2 - 1;
            y = (y / Config::SCR_HEIGHT) * 2 - 1;
            // random colors
            std::vector <float> color = {static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
                                         static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
                                         static_cast <float> (rand()) / static_cast <float> (RAND_MAX)};
            circles->push_back(Circle(circles->size() + 1, x, -y, 0.05f, 100, 0.5f, color));
            isPressed = true;
        }
    } else {
        isPressed = false;
    }

    // remove all circles on space
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        circles->clear();
    }

    // remove the last circle on backspace
    static bool isBackspacePressed = false;
    if (glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS) {
        if (!isBackspacePressed && !circles->empty()) {
            circles->pop_back();
            isBackspacePressed = true;
        }
    } else {
        isBackspacePressed = false;
    }

    // increase the mass of the last circle on up arrow
    static bool isUpPressed = false;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        if (!isUpPressed && !circles->empty()) {
            circles->back().mass += 100000000.0f;
            isUpPressed = true;
        }
    } else {
        isUpPressed = false;
    }
}