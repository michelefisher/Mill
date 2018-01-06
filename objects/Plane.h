#pragma once

#include "ColoredCube.h"

class Plane : public BasicObject {
public:
    Plane(BasicShader* shaderProgram, Camera* camera, float length, glm::vec3 color);

    void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

    static const vector<float> planeCoords;
    static const vector<unsigned> indices;
private:
    glm::vec3 planeColor;
};
