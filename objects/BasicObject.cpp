#include <algorithm>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "BasicObject.h"

using namespace std;

BasicObject::BasicObject() : shaderProgram(nullptr),
                             model(glm::mat4()) {}

BasicObject::BasicObject(ShaderProgram* shaderProgram, Camera* camera) : shaderProgram(shaderProgram),
                                                                         camera(camera),
                                                                         model(glm::mat4())
{}

BasicObject::BasicObject(Camera *camera, ShaderProgram *shaderProgram, const vector<float> &verticesCoords,
                         const vector<float> &verticesTextureCoords, const vector<unsigned> &indices) : indices(indices),
                                                                                                        shaderProgram(shaderProgram),
                                                                                                        camera(camera)
{
    for (int i = 0, s = verticesCoords.size(); i < (s / 3); ++i) {
        int index = i * 3;

        for (int j = index; j < index + 3; ++j) {
            vertices.push_back(verticesCoords[j]);
        }

        for (int j = i * 2; j < i * 2 + 2; ++j) {
            vertices.push_back(verticesTextureCoords[j]);
        }
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(GLfloat), &this->vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

BasicObject::BasicObject(Camera *camera, ShaderProgram *shaderProgram, const vector<float> &verticesCoords,
                         const glm::vec3 &color, const vector<unsigned> &indices) :
        indices(indices),
        shaderProgram(shaderProgram), camera(camera)

{
    for (int i = 0, s = verticesCoords.size(); i < (s / 3); ++i) {
        int index = i * 3;

        for (int j = index; j < index + 3; ++j) {
            vertices.push_back(verticesCoords[j]);
        }

        vertices.push_back(color.x);
        vertices.push_back(color.y);
        vertices.push_back(color.z);
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(GLfloat), &this->vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void BasicObject::draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    shaderProgram->use();

    shaderProgram->setMat4("model", model);
    shaderProgram->setMat4("view", viewMatrix);
    shaderProgram->setMat4("projection", projectionMatrix);

    setShaderSpecificUniforms();

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void BasicObject::translate(const glm::vec3& vector) {
    model = glm::translate(model, vector);
}

void BasicObject::scale(const glm::vec3& vector) {
    model = glm::scale(model, vector);
}

void BasicObject::rotate(float angle, const glm::vec3& axis) {
    model = glm::rotate(model, glm::radians(angle), axis);
}

void BasicObject::bindTexture(GLuint texture, unsigned short textureUnitNumber) {
    glActiveTexture(GL_TEXTURE0 + textureUnitNumber);
    glBindTexture(GL_TEXTURE_2D, texture);
}

void BasicObject::unBindTexture() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

ShaderProgram *BasicObject::getShaderProgram() const {
    return shaderProgram;
}
