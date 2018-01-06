#pragma once

#include "BasicObject.h"

class Skybox : public BasicObject {
public:
    Skybox(BasicShader* shaderProgram, vector<std::string>& facesPaths);

    void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
    unsigned loadCubemap(vector<std::string>& facesPaths);

    static const vector<float> verticesCoords;

private:
    unsigned textureID;
};