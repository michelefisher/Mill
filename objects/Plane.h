#pragma once

#include "ColoredCube.h"

class Plane : public BasicObject {
public:
    Plane(BasicShader* shaderProgram, Camera* camera, float length, glm::vec3 color);

    static const vector<float> planeCoords;
    static const vector<unsigned> indices;
private:
    void setObjectRelatedUniforms();

    glm::vec3 planeColor;
public:
};
