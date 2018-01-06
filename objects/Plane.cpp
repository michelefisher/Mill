#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <iostream>
#include "Plane.h"

const vector<float> Plane::planeCoords = {
        -0.5f, 0.0f, 0.5f,
        -0.5f, 0.0f, -0.5f,
        0.5f, 0.0f, 0.5f,
        0.5f, 0.0f, -0.5f
};

const vector<unsigned> Plane::indices = {
        0, 1, 3,
        3, 2, 0
};


Plane::Plane(BasicShader* shaderProgram, Camera* camera, float length, glm::vec3 color)
        : BasicObject(camera, shaderProgram, Plane::planeCoords, color, Plane::indices), planeColor(color) {

    float yWidth = 1.0f/length * 0.01f;

    model = glm::scale(model, glm::vec3(length, yWidth, length));
}

void Plane::draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    shaderProgram->use();

    shaderProgram->setMat4("model", model);
    shaderProgram->setMat4("view", viewMatrix);
    shaderProgram->setMat4("projection", projectionMatrix);
    shaderProgram->setLightColorToGlobalColor();

    shaderProgram->setVec3("objectColor", planeColor);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

