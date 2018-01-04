#pragma once

#include "BasicObject.h"

class ColoredCube : public BasicObject {
public:
    ColoredCube();
    ColoredCube(ShaderProgram* shaderProgram, Camera* camera, float sideLength, glm::vec3 sideColor = glm::vec3(0.0f, 0.5f, 0.0f));

    void setLightColor(const glm::vec3 &lightColor);

    static const vector<float> cubeCoords;
    static const vector<float> textureCoords;
    static const vector<unsigned> indices;
private:
    void setShaderSpecificUniforms();
    glm::vec3 sideColor;
    glm::vec3 lightColor;
};

