#pragma once

#include "BasicObject.h"

class Cube : public BasicObject {
public:
    Cube();
    Cube(ShaderProgram* shaderProgram, Camera* camera, float sideLength, glm::vec3 sideColor = glm::vec3(0.0f, 0.5f, 0.0f));
    Cube(ShaderProgram* shaderProgram, Camera* camera, float sideLength, const vector<float>& textureCoords = Cube::textureCoords);

    static const vector<float> cubeCoords;
    static const vector<float> textureCoords;
    static const vector<unsigned> indices;
private:
};

