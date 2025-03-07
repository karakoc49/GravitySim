#include "circle.h"

#include <cmath>
#include <iomanip>
#include <iostream>

#include "constants.h"

void Circle::update(float dt) {
    vx += ax * dt;
    vy += ay * dt;
    x += vx * dt;
    y += vy * dt;

    // Apply gravity and collision handling
    ay = Physics::GRAVITY;
    if (y - radius < -Physics::LIMIT_LEN) {
        y = -Physics::LIMIT_LEN + radius;
        vy = -vy * Physics::ELASTICITY;
    }

    if (y + radius > 1.0f) {
        y = Physics::LIMIT_LEN - radius;
        vy = -vy * Physics::ELASTICITY;
    }

    // Collision with screen's left side
    if (x - radius < -Physics::LIMIT_LEN) {
        x = -Physics::LIMIT_LEN + radius;
        vx = -vx * Physics::ELASTICITY;
    }

    // Collision with screen's right side
    if (x + radius > Physics::LIMIT_LEN) {
        x = Physics::LIMIT_LEN - radius;
        vx = -vx * Physics::ELASTICITY;
    }

    // Ensure velocities are not NaN
    if (std::isnan(vx)) vx = 0.0f;
    if (std::isnan(vy)) vy = 0.0f;

    // Ensure positions are not NaN
    if (std::isnan(x)) x = 0.0f;
    if (std::isnan(y)) y = 0.0f;
}

void Circle::applyGravity(const std::vector<Circle>& circles) {
    for (const auto& other : circles) {
        if (&other == this) continue;  // Skip self

        // Calculate the distance between centers
        float dx = other.x - x;
        float dy = other.y - y;
        float r = sqrt(dx * dx + dy * dy);

        // Apply gravitational force
        float force = Physics::G * (mass * other.mass) / (r * r);
        float ax = force * dx / (mass * r);  // Acceleration in x-direction
        float ay = force * dy / (mass * r);  // Acceleration in y-direction

        // Update acceleration
        this->ax += ax;
        this->ay += ay;
    }
}

bool Circle::checkCollision(const Circle &other) {
    float dx = other.x - x;
    float dy = other.y - y;
    float distance = std::sqrt(dx * dx + dy * dy);
    return distance < (radius + other.radius);
}

void Circle::resolveCollision(Circle &other) {
    if (!checkCollision(other)) return;

    float dx = other.x - x;
    float dy = other.y - y;
    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance == 0.0f) return; // Avoid division by zero

    // Normal vector
    float nx = dx / distance;
    float ny = dy / distance;

    // Relative velocity
    float rvx = other.vx - vx;
    float rvy = other.vy - vy;

    // Relative velocity in terms of the normal direction
    float velAlongNormal = rvx * nx + rvy * ny;

    // Do not resolve if velocities are separating
    if (velAlongNormal > 0) return;

    // Calculate restitution (elasticity)
    float e = 0.8f; // Coefficient of restitution

    // Calculate impulse scalar
    float j = -(1 + e) * velAlongNormal;
    j /= (1 / mass + 1 / other.mass);

    // Apply impulse
    float impulseX = j * nx;
    float impulseY = j * ny;

    vx -= impulseX / mass;
    vy -= impulseY / mass;
    other.vx += impulseX / other.mass;
    other.vy += impulseY / other.mass;

    // Correct positions to avoid sinking
    float percent = 0.2f; // Penetration percentage to correct
    float correction = (radius + other.radius - distance) / (1 / mass + 1 / other.mass) * percent;
    float correctionX = correction * nx;
    float correctionY = correction * ny;

    x -= correctionX / mass;
    y -= correctionY / mass;
    other.x += correctionX / other.mass;
    other.y += correctionY / other.mass;
}

void Circle::printAttributes() {
    std::cout << "\rCircle " << id << " at (" << std::fixed << std::setprecision(2)
              << x << ", " << y << ") | Velocity: (" << vx << ", " << vy << ")"
              << " | Mass: " << mass << " | Radius: " << radius
              << std::flush;  // Flush the output to ensure it is printed immediately
}
