#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "circle.h"

class Renderer {
public:
    void render(const std::vector<Circle>& circles);
};

#endif
