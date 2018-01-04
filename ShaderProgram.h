#pragma once

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

class ShaderProgram
{
public:
    ShaderProgram(const char* vertexPath, const char* fragmentPath);
    void use();
    void setBool(const std::string&, bool) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
    void setVec3(const std::string& name, const glm::vec3& vec) const;
private:
    unsigned int programID;

    void checkCompilationErrors(unsigned shaderID, GLenum type);
    void checkLinkingErrors();
    std::string readShaderCode(const char* shaderPath);
    unsigned compileShader(const char** shaderSource, GLenum type);
    void linkProgram(unsigned vertexShader, unsigned fragmentShader);
};