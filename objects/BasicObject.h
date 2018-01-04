#pragma once

#include <vector>
#include "../ShaderProgram.h"
#include "Camera.h"

using namespace std;

class BasicObject {
public:
    BasicObject();
    BasicObject(ShaderProgram*, Camera*);
    BasicObject(Camera *, ShaderProgram *, const vector<float> &, const vector<float> &, const vector<unsigned> &);
    BasicObject(Camera *, ShaderProgram *, const vector<float> &, const glm::vec3 &, const vector<unsigned> &);

    void bindTexture(unsigned, unsigned short);
    void unBindTexture();

    void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

    virtual void setShaderSpecificUniforms() { return; }

    void translate(const glm::vec3& vector);
    void scale(const glm::vec3& vector);
    void rotate(float angle, const glm::vec3& axis);

    ShaderProgram *getShaderProgram() const;
protected:
    glm::mat4 model;
    vector<float> vertices;
    vector<unsigned> indices;
    unsigned VAO, VBO, EBO;
    ShaderProgram* shaderProgram;
    Camera* camera;
};
