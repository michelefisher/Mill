#pragma once

#include <vector>
#include "../ShaderProgram.h"
#include "Camera.h"

using namespace std;

class BasicObject {
public:
    BasicObject();
    BasicObject(const vector<float>&, const vector<float>&, const vector<unsigned >&);
    BasicObject(const vector<float>&, const vector<float>&, const vector<unsigned >&, ShaderProgram*, Camera*);
    void bindTexture(unsigned, unsigned short);
    void unBindTexture();

    void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

    ShaderProgram *getShaderProgram() const;
    void setModel(const glm::mat4 &model);
protected:

protected:
    glm::mat4 model;

    void moveDataToGPU();

    vector<float> vertices;
    vector<unsigned> indices;
    unsigned VAO, VBO, EBO;
    ShaderProgram* shaderProgram;
    Camera* camera;
};