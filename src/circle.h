#ifndef CIRCLE_H
#define CIRCLE_H

#include <vector>

struct Circle {
    int id;
    float x, y;
    float radius;
    int numSegments;
    std::vector<float> color;
    float vx, vy;
    float ax, ay;
    float mass;

    Circle(int id, float x, float y, float radius, int numSegments = 30, float mass = 10000.0f, std::vector<float> color = {1.0f, 1.0f, 1.0f})
        : id(id), x(x), y(y), radius(radius), numSegments(numSegments), mass(mass), color(color) {
    }

    void update(float dt);

    void applyGravity(const std::vector<Circle> &circles);

    bool checkCollision(const Circle &other);

    void resolveCollision(Circle &other);

    void printAttributes();
};

#endif