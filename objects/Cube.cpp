#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "Cube.h"


const vector<float> Cube::cubeCoords = {
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

const vector<float> Cube::textureCoords = {
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

const vector<unsigned> Cube::indices = {
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

Cube::Cube() : Cube(nullptr, nullptr, 1.0f, glm::vec3(0.0f, 0.5f, 0.0f)) {}

Cube::Cube(ShaderProgram* shaderProgram, Camera* camera, float sideLength, glm::vec3 sideColor)
        : BasicObject(Cube::cubeCoords, sideColor, Cube::indices, shaderProgram, camera) {
    model = glm::scale(model, glm::vec3(sideLength, sideLength, sideLength));
}

Cube::Cube(ShaderProgram* shaderProgram, Camera* camera, float sideLength, const vector<float>& textureCoords)
        : BasicObject(Cube::cubeCoords, textureCoords, Cube::indices, shaderProgram, camera) {
    model = glm::scale(model, glm::vec3(sideLength, sideLength, sideLength));
}