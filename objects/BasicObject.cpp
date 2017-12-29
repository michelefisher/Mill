#include <algorithm>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "BasicObject.h"

using namespace std;

BasicObject::BasicObject() : shaderProgram(nullptr),
                             model(glm::mat4()) {}

BasicObject::BasicObject(ShaderProgram* shaderProgram, Camera* camera) : shaderProgram(shaderProgram),
                                                                         camera(camera),
                                                                         model(glm::mat4())
{}

BasicObject::BasicObject(const vector<GLfloat>& verticesCoords, const vector<GLfloat>& verticesTextureCoords,
                         const vector<GLuint>& indices, ShaderProgram* shaderProgram, Camera* camera): indices(indices),
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

BasicObject::BasicObject(const vector<GLfloat>& verticesCoords, const glm::vec3& color, const vector<GLuint>& indices,
                         ShaderProgram* shaderProgram, Camera* camera):
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
/*
BasicObject BasicObject::createObjWithColor(const vector<float>& vertsCoords, const vector<float>& vertsColors,
                                              const vector<unsigned>& indices, ShaderProgram* shaderProgram,
                                              Camera* camera) {
    BasicObject basicObject(shaderProgram, camera);
    basicObject.setIndices(indices);

    unsigned int& VBO = basicObject.getVBO();
    unsigned int& VAO = basicObject.getVAO();
    unsigned int& EBO = basicObject.getEBO();

    vector<float>& vertices = basicObject.getVertices();
    for (int i = 0, s = vertsCoords.size(); i < (s / 3); ++i) {
        int index = i * 3;

        for (int j = index; j < index + 3; ++j) {
            vertices.push_back(vertsCoords[j]);
        }

        for (int j = index; j < index + 3; ++j) {
            vertices.push_back(vertsColors[j]);
        }
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return basicObject;
}

BasicObject BasicObject::createObjWithTexture(const vector<float>& vertsCoords, const vector<float>& vertsTextureCoords,
                                            const vector<unsigned>& indices, ShaderProgram* shaderProgram,
                                            Camera* camera) {
    unsigned int VBO, VAO, EBO;

    BasicObject basicObject(shaderProgram, camera);
    basicObject.setIndices(indices);

    vector<float>& vertices = basicObject.getVertices();
    for (int i = 0, s = vertices.size(); i < (s / 3); ++i) {
        int index = i * 3;

        for (int j = index; j < index + 3; ++j) {
            vertices.push_back(vertsCoords[j]);
        }

        for (int j = i * 2; j < i * 2 + 2; ++j) {
            vertices.push_back(vertsTextureCoords[j]);
        }
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return basicObject;
};
*/
void BasicObject::moveDataToGPU() {
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

void BasicObject::draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    shaderProgram->use();

    shaderProgram->setMat4("model", model);
    shaderProgram->setMat4("view", viewMatrix);
    shaderProgram->setMat4("projection", projectionMatrix);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
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

void BasicObject::setModel(const glm::mat4 &model) {
    this->model = model;
}

vector<float>& BasicObject::getVertices() {
    return vertices;
}

void BasicObject::setVertices(const vector<float> &vertices) {
    this->vertices = vertices;
}

const vector<unsigned int>& BasicObject::getIndices() const {
    return indices;
}

void BasicObject::setIndices(const vector<unsigned int> &indices) {
    this->indices = indices;
}

void BasicObject::setVAO(unsigned int VAO) {
    this->VAO = VAO;
}

void BasicObject::setVBO(unsigned int VBO) {
    this->VBO = VBO;
}

void BasicObject::setEBO(unsigned int EBO) {
    this->EBO = EBO;
}

unsigned int& BasicObject::getVAO() {
    return VAO;
}

unsigned int& BasicObject::getVBO() {
    return VBO;
}

unsigned int& BasicObject::getEBO() {
    return EBO;
}
