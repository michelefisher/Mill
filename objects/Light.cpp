#include "Light.h"

Light::Light() : Light(nullptr, nullptr) {};

Light::Light(BasicShader* shaderProgram, Camera* camera, glm::vec3 lightColor) :
    ColoredCube(shaderProgram, camera, 1.0f, lightColor), lightColor(lightColor) {}

void Light::setShaderSpecificUniforms() {
    shaderProgram->setVec3("lightColor",  lightColor);
}

const glm::vec3 &Light::getLightColor() const {
    return lightColor;
}

