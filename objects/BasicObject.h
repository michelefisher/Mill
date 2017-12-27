#pragma once
#include <GL/glew.h>
#include <vector>
#include "../ShaderProgram.h"

using namespace std;

class BasicObject {
public:
    BasicObject();
    BasicObject(const vector<GLfloat>&, const vector<GLfloat>&, const vector<GLuint>&);
    BasicObject(const vector<GLfloat>&, const vector<GLfloat>&, const vector<GLfloat>&, const vector<GLuint>&);
    BasicObject(const vector<GLfloat>&, const vector<GLfloat>&, const vector<GLuint>&, ShaderProgram*);
    BasicObject(const vector<GLfloat>&, const vector<GLfloat>&, const vector<GLfloat>&, const vector<GLuint>&, ShaderProgram*);
    void bindTexture(GLuint, unsigned short);
    void unBindTexture();

    void draw();

private:
    vector<GLfloat> vertices;
    vector<GLuint> indices;
    GLuint VAO, VBO, EBO;
    ShaderProgram* shaderProgram;
};