#include "Light.h"

Light::Light() : Light(nullptr, nullptr) {};

Light::Light(BasicShader* shaderProgram, Camera* camera, glm::vec3 lightColor) :
    ColoredCube(shaderProgram, camera, 1.0f, lightColor), lightColor(lightColor) {}

void Light::draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    shaderProgram->use();

    shaderProgram->setMat4("model", model);
    shaderProgram->setMat4("view", viewMatrix);
    shaderProgram->setMat4("projection", projectionMatrix);
    shaderProgram->setLightColorToGlobalColor();

    shaderProgram->setVec3("lightColor",  lightColor);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

const glm::vec3 &Light::getLightColor() const {
    return lightColor;
}

