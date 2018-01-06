#pragma once

#include "ColoredCube.h"

class Light : public ColoredCube {
public:
    Light();
    Light(BasicShader* shaderProgram, Camera* camera, glm::vec3 lightColor = glm::vec3(0.0f, 0.5f, 0.0f));

    void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

    const glm::vec3 &getLightColor() const;
private:
    glm::vec3 lightColor;
};