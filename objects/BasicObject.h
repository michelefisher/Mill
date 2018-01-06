#pragma once

#include <vector>
#include "../shaders/cpp/BasicShader.h"
#include "Camera.h"

using namespace std;

class BasicObject {
public:
    BasicObject();
    BasicObject(BasicShader*, Camera*);
    BasicObject(Camera *, BasicShader *, const vector<float> &, const vector<float> &, const vector<unsigned> &);
    BasicObject(Camera *, BasicShader *, const vector<float> &, const glm::vec3 &, const vector<unsigned> &);

    void bindTexture(unsigned, unsigned short);
    void unBindTexture();

    virtual void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) = 0;

    void translate(const glm::vec3& vector);
    void scale(const glm::vec3& vector);
    void rotate(float angle, const glm::vec3& axis);

    BasicShader *getShaderProgram() const;
protected:
    glm::mat4 model;
    vector<float> vertices;
    vector<unsigned> indices;
    unsigned VAO, VBO, EBO;
    BasicShader* shaderProgram;
    Camera* camera;
};
