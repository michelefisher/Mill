#pragma once
#include <GL/glew.h>
#include <string>
#include <map>

using namespace std;

class ShaderProgram {
public:
    ShaderProgram(const string&, const string&, const string& = string());
    ~ShaderProgram();
    void useProgram();
    void unUseProgram();
    void addAttribute(const string&);
    GLint getAttribute(const string&);
    void addUniform(const string&);
    GLint getUniform(const string&);
    void deleteProgram();

private:
    ShaderProgram();
    string loadShaderSourceFromFile(const string &);
    void compileShader(GLenum, const string &);
    void createAndLinkProgram();
    void throwErrorWithMsg(GLuint, const string &, void (*parameterAccessFunc)(GLuint, GLenum, GLint *),
                           void (*informationLogFunc)(GLuint, GLsizei, GLsizei *, GLchar *));

    map<GLenum, GLuint> shaders;
    map<string, GLint> attributesList;
    map<string, GLint> uniformsList;
    GLuint program;
};
