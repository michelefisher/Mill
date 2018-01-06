#pragma once

#include "BasicObject.h"

class ColoredCube : public BasicObject {
public:
    ColoredCube();
    ColoredCube(BasicShader* shaderProgram, Camera* camera, float sideLength, glm::vec3 sideColor = glm::vec3(0.0f, 0.5f, 0.0f));

    void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

    static const vector<float> verticesCoords;
    static const vector<float> textureCoords;
    static const vector<unsigned> indices;
private:
    glm::vec3 sideColor;
};

