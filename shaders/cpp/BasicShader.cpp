#include <fstream>
#include <sstream>
#include <iostream>
#include "BasicShader.h"


BasicShader::BasicShader(const char* vertexPath, const char* fragmentPath, glm::vec3 lightColor) :
        lightColor(lightColor) {
    std::string _vertexCode = readShaderCode(vertexPath);
    std::string _fragmentCode = readShaderCode(fragmentPath);
    const char* vertexCode = _vertexCode.c_str();
    const char * fragmentCode = _fragmentCode.c_str();
    unsigned vertex = compileShader(&vertexCode, GL_VERTEX_SHADER);
    unsigned fragment = compileShader(&fragmentCode, GL_FRAGMENT_SHADER);

    linkProgram(vertex, fragment);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void BasicShader::use() {
    glUseProgram(programID);
}

std::string BasicShader::readShaderCode(const char* shaderPath) {
    std::string shaderCode;
    std::ifstream shaderFile;

    try {
        std::stringstream shaderStream;

        shaderFile.open(shaderPath);
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();

        shaderCode = shaderStream.str();
    } catch (std::ifstream::failure& error) {
        std::cerr << "An error occured during read of the file: " << shaderPath << std::endl;
    }

    return shaderCode;
}

unsigned BasicShader::compileShader(const char** shaderSource, GLenum type) {
    unsigned shaderID = glCreateShader(type);

    glShaderSource(shaderID, 1, shaderSource, nullptr);
    glCompileShader(shaderID);
    checkCompilationErrors(shaderID, type);

    return shaderID;
}

void BasicShader::linkProgram(unsigned vertexShader, unsigned fragmentShader) {
    programID = glCreateProgram();

    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);
    checkLinkingErrors();
}

void BasicShader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
}

void BasicShader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

void BasicShader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}

void BasicShader::setMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void BasicShader::setVec3(const std::string& name, const glm::vec3& vec) const {
    glUniform3fv(glGetUniformLocation(programID, name.c_str()), 1, &vec[0]);
}

void BasicShader::setLightColorToGlobalColor() const {
    setVec3("lightColor", lightColor);
}

void BasicShader::checkCompilationErrors(unsigned shaderID, GLenum type)
{
    int success;
    char infoLog[1024];

    std::string shaderType = (type == GL_VERTEX_SHADER) ? "Vertex" : "Fragment";

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
        throw std::runtime_error(shaderType + "compilation error: " + infoLog);
    }
}

void BasicShader::checkLinkingErrors()
{
    int success;
    char infoLog[1024];

    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(programID, 1024, nullptr, infoLog);
        std::stringstream errorStream;
        errorStream << "Shader program linking error: ";
        errorStream << infoLog;

        throw std::runtime_error(errorStream.str());
    }
}
