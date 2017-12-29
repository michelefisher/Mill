#pragma once

#include <vector>
#include "../ShaderProgram.h"
#include "Camera.h"

using namespace std;

class BasicObject {
public:
    BasicObject();
    BasicObject(ShaderProgram*, Camera*);
    BasicObject(const vector<float>&, const vector<float>&, const vector<unsigned >&, ShaderProgram*, Camera*);
    BasicObject(const vector<float>&, const glm::vec3&, const vector<unsigned>&, ShaderProgram*, Camera*);

    void bindTexture(unsigned, unsigned short);
    void unBindTexture();

    void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

    ShaderProgram *getShaderProgram() const;
    void setModel(const glm::mat4 &model);

    vector<float>& getVertices();

    void setVertices(const vector<float> &vertices);

    const vector<unsigned int> &getIndices() const;

    void setIndices(const vector<unsigned int> &indices);

    void setVAO(unsigned int VAO);
    void setVBO(unsigned int VBO);
    void setEBO(unsigned int EBO);
    unsigned int& getVAO();
    unsigned int& getVBO();
    unsigned int& getEBO();
protected:

    glm::mat4 model;

    void moveDataToGPU();
    vector<float> vertices;
    vector<unsigned> indices;
    unsigned VAO, VBO, EBO;
    ShaderProgram* shaderProgram;
    Camera* camera;
};
