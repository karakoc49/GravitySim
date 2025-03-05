#include "renderer.h"
#include <GLFW/glfw3.h>
#include <cmath>

void Renderer::render(const std::vector<Circle>& circles) {
    glClear(GL_COLOR_BUFFER_BIT);

    for (const auto& circle : circles) {
        glColor3f(circle.color[0], circle.color[1], circle.color[2]);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(circle.x, circle.y); // Center

        for (int i = 0; i <= circle.numSegments; i++) {
            float angle = (i / (float)circle.numSegments) * 2.0f * M_PI;
            float xPos = circle.x + circle.radius * cos(angle);
            float yPos = circle.y + circle.radius * sin(angle);
            glVertex2f(xPos, yPos);
        }

        glEnd();
    }

}