#pragma once

#include "Cube.h"

class Plane : public BasicObject {
public:
    Plane(ShaderProgram* shaderProgram, Camera* camera, float length, glm::vec3 color);

    static const vector<float> planeCoords;
    static const vector<unsigned> indices;
};
