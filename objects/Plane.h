#pragma once

#include "ColoredCube.h"

class Plane : public BasicObject {
public:
    Plane(ShaderProgram* shaderProgram, Camera* camera, float length, glm::vec3 color);

    void setLightColor(const glm::vec3 &lightColor);

    static const vector<float> planeCoords;
    static const vector<unsigned> indices;
private:
    void setShaderSpecificUniforms();

    glm::vec3 planeColor;
    glm::vec3 lightColor;
public:
};
