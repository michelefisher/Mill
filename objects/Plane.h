#pragma once

#include "Cube.h"

class Plane : public Cube {
public:
    explicit Plane(float, glm::vec3 = glm::vec3(0.0f, 0.0f, 0.0f));
    Plane(float, glm::vec3, ShaderProgram*, Camera*);
};
