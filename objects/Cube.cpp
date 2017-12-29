#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "Cube.h"

Cube::Cube() : Cube(1.0f) {}

Cube::Cube(float sideLength) : BasicObject() {
    shaderProgram = nullptr;
    camera = nullptr;

     vertices = {
            -0.5f*sideLength, -0.5f*sideLength, -0.5f*sideLength,  0.0f, 0.0f,
            0.5f*sideLength, -0.5f*sideLength, -0.5f*sideLength,  1.0f, 0.0f,
            0.5f*sideLength,  0.5f*sideLength, -0.5f*sideLength,  1.0f, 1.0f,
            -0.5f*sideLength,  0.5f*sideLength, -0.5f*sideLength,  0.0f, 1.0f,

            -0.5f*sideLength, -0.5f*sideLength,  0.5f*sideLength,  0.0f, 0.0f,
            0.5f*sideLength, -0.5f*sideLength,  0.5f*sideLength,  1.0f, 0.0f,
            0.5f*sideLength,  0.5f*sideLength,  0.5f*sideLength,  1.0f, 1.0f,
            -0.5f*sideLength,  0.5f*sideLength,  0.5f*sideLength,  0.0f, 1.0f,

            -0.5f*sideLength,  0.5f*sideLength,  0.5f*sideLength,  1.0f, 0.0f,
            -0.5f*sideLength,  0.5f*sideLength, -0.5f*sideLength,  1.0f, 1.0f,
            -0.5f*sideLength, -0.5f*sideLength, -0.5f*sideLength,  0.0f, 1.0f,
            -0.5f*sideLength, -0.5f*sideLength,  0.5f*sideLength,  0.0f, 0.0f,

            0.5f*sideLength,  0.5f*sideLength,  0.5f*sideLength,  1.0f, 0.0f,
            0.5f*sideLength,  0.5f*sideLength, -0.5f*sideLength,  1.0f, 1.0f,
            0.5f*sideLength, -0.5f*sideLength, -0.5f*sideLength,  0.0f, 1.0f,
            0.5f*sideLength, -0.5f*sideLength,  0.5f*sideLength,  0.0f, 0.0f,

            -0.5f*sideLength, -0.5f*sideLength, -0.5f*sideLength,  0.0f, 1.0f,
            0.5f*sideLength, -0.5f*sideLength, -0.5f*sideLength,  1.0f, 1.0f,
            0.5f*sideLength, -0.5f*sideLength,  0.5f*sideLength,  1.0f, 0.0f,
            -0.5f*sideLength, -0.5f*sideLength, 0.5f*sideLength,  0.0f, 0.0f,

            -0.5f*sideLength,  0.5f*sideLength, -0.5f*sideLength,  0.0f, 1.0f,
            0.5f*sideLength,  0.5f*sideLength, -0.5f*sideLength,  1.0f, 1.0f,
            0.5f*sideLength,  0.5f*sideLength,  0.5f*sideLength,  1.0f, 0.0f,
            -0.5f*sideLength,  0.5f*sideLength,  0.5f*sideLength,  0.0f, 0.0f,
    };

    indices = {
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

    moveDataToGPU();
}

Cube::Cube(float sideLength, ShaderProgram* shaderProgram, Camera* camera) : Cube(sideLength) {
    this->shaderProgram = shaderProgram;
    this->camera = camera;
}