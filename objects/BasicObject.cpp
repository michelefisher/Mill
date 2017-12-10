#include <algorithm>

#include "BasicObject.h"

using namespace std;

BasicObject::BasicObject() : shaderProgram(nullptr) {}

BasicObject::BasicObject(const vector<GLfloat>& verticesCoords, const vector<GLfloat>& verticesColors,
                         const vector<GLuint>& indices) : BasicObject() {
    this->indices = indices;
    for (int i = 0, s = verticesCoords.size(); i < (s / 3); ++i) {
        int index = i * 3;

        for (int j = index; j < index + 3; ++j) {
            vertices.push_back(verticesCoords[j]);
        }

        for (int j = index; j < index + 3; ++j) {
            vertices.push_back(verticesColors[j]);
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

BasicObject::BasicObject(const vector<GLfloat>& verticesCoords, const vector<GLfloat>& verticesColors,
                         const vector<GLfloat>& verticesTextureCoords, const vector<GLuint>& indices) : BasicObject() {
    this->indices = indices;
    for (int i = 0, s = verticesCoords.size(); i < (s / 3); ++i) {
        int index = i * 3;

        for (int j = index; j < index + 3; ++j) {
            vertices.push_back(verticesCoords[j]);
        }

        for (int j = index; j < index + 3; ++j) {
            vertices.push_back(verticesColors[j]);
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6* sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

BasicObject::BasicObject(const vector<GLfloat>& verticesCoords, const vector<GLfloat>& verticesColors,
                         const vector<GLuint>& indices, ShaderProgram* shaderProgram) :
        BasicObject(verticesCoords, verticesColors, indices) {
    this->shaderProgram = shaderProgram;
}

BasicObject::BasicObject(const vector<GLfloat>& verticesCoords, const vector<GLfloat>& verticesColors,
                         const vector<GLfloat>& verticesTextureCoords, const vector<GLuint>& indices,
                         ShaderProgram* shaderProgram) :
        BasicObject(verticesCoords, verticesColors, verticesTextureCoords, indices) {
    this->shaderProgram = shaderProgram;
}


void BasicObject::bindTexture(GLuint texture, unsigned short textureUnitNumber) {
    glActiveTexture(GL_TEXTURE0 + textureUnitNumber);
    glBindTexture(GL_TEXTURE_2D, texture);
}

void BasicObject::unBindTexture() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void BasicObject::draw() {
    shaderProgram->useProgram();


    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    shaderProgram->unUseProgram();
}