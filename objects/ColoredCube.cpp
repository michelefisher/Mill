#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "ColoredCube.h"


const vector<float> ColoredCube::verticesCoords = {
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            -0.5f, 0.5f, -0.5f,

            -0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,

            -0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, 0.5f,

            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, 0.5f,

            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, 0.5f,
            -0.5f, -0.5f, 0.5f,

            -0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,
};

const vector<float> ColoredCube::textureCoords = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
};

const vector<unsigned> ColoredCube::indices = {
        0, 1, 2,
        3, 2, 0,

        4, 5, 6,
        7, 6, 4,

        8, 9, 10,
        11, 10, 8,

        12, 13, 14,
        15, 14, 12,

        16, 17, 18,
        19, 18, 16,

        20, 21, 22,
        23, 22, 20
};

ColoredCube::ColoredCube() : ColoredCube(nullptr, nullptr, 1.0f, glm::vec3(0.0f, 0.5f, 0.0f)) {}

ColoredCube::ColoredCube(BasicShader* shaderProgram, Camera* camera, float sideLength, glm::vec3 sideColor)
        : BasicObject(camera, shaderProgram, ColoredCube::verticesCoords, sideColor, ColoredCube::indices) {
    model = glm::scale(model, glm::vec3(sideLength, sideLength, sideLength));
    this->sideColor = sideColor;
}

void ColoredCube::draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    shaderProgram->use();

    shaderProgram->setMat4("model", model);
    shaderProgram->setMat4("view", viewMatrix);
    shaderProgram->setMat4("projection", projectionMatrix);
    shaderProgram->setLightColorToGlobalColor();

    shaderProgram->setVec3("objectColor", sideColor);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
