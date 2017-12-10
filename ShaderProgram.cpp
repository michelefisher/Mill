#include <fstream>
#include <sstream>
#include "ShaderProgram.h"

ShaderProgram::ShaderProgram() {
    shaders.clear();
    attributesList.clear();
    uniformsList.clear();

    program = 0;
}

ShaderProgram::ShaderProgram(const string& vertexShaderFileName, const string& fragmentShaderFileName,
                             const string& geometryShaderFileName) : ShaderProgram() {
    string geometryShaderSource;

    // Load vertex and fragment shaders
    string vertexShaderSource = loadShaderSourceFromFile(vertexShaderFileName);
    string fragmentShaderSource = loadShaderSourceFromFile(fragmentShaderFileName);

    // Compile vertex and fragment shaders
    compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    // If present, load and compile geometry shader
    if (!geometryShaderFileName.empty()) {
        geometryShaderSource = loadShaderSourceFromFile(geometryShaderFileName);
        compileShader(GL_GEOMETRY_SHADER, geometryShaderSource);
    }

    // Create program, attach shaders and link them
    createAndLinkProgram();
}

ShaderProgram::~ShaderProgram() {
    shaders.clear();
    attributesList.clear();
    uniformsList.clear();
}

string ShaderProgram::loadShaderSourceFromFile(const string &fileName) {
    ifstream shaderDefinitionStream;
    shaderDefinitionStream.open(fileName.c_str(), ios_base::in);
    if (!shaderDefinitionStream) {
        throw runtime_error("Error while opening file: " + fileName);
    }

    string line, buffer;
    while(getline(shaderDefinitionStream, line)) {
        buffer.append(line);
        buffer.append("\r\n");
    }

    return buffer;
}

void ShaderProgram::compileShader(GLenum shaderType, const string& shaderSource) {
    GLint shaderCompilationStatus;

    const char* _shaderSource =  shaderSource.c_str();

    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &_shaderSource, nullptr);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompilationStatus);
    if (shaderCompilationStatus == GL_FALSE) {
        string shaderTypeStr = string();

        // TODO: Ugly. Maybe shader type can be set in some simpler way?
        if (shaderType == GL_VERTEX_SHADER) shaderTypeStr = "Vertex";
        else if (shaderType == GL_FRAGMENT_SHADER) shaderTypeStr = "Fragment";
        else shaderTypeStr = "Geometry";

        throwErrorWithMsg(shader, shaderTypeStr + " shader compilation error: ", glGetShaderiv, glGetShaderInfoLog);
    }

    shaders[shaderType] = shader;
}

void ShaderProgram::createAndLinkProgram() {
    program = glCreateProgram();
    GLint linkingStatus;

    for (auto& pair: shaders) {
        if (pair.second != 0) {
            glAttachShader(program, pair.second);
        }
    }

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &linkingStatus);
    if (linkingStatus == GL_FALSE) {
        throwErrorWithMsg(program, "Program linking error", glGetProgramiv, glGetProgramInfoLog);
    }

    for (auto& pair: shaders) {
        glDeleteShader(pair.second);
    }
}

void ShaderProgram::useProgram() {
    glUseProgram(program);
}

void ShaderProgram::unUseProgram() {
    glUseProgram(0);
}

void ShaderProgram::addAttribute(const string& attribute) {
    attributesList[attribute] = glGetAttribLocation(program, attribute.c_str());
}

GLint ShaderProgram::getAttribute(const string& attribute) {
    return attributesList[attribute];
}

void ShaderProgram::addUniform(const string & uniform) {
    uniformsList[uniform] = glGetUniformLocation(program, uniform.c_str());
}

GLint ShaderProgram::getUniform(const string& uniform) {
    return uniformsList[uniform];
}

void ShaderProgram::deleteProgram() {
    glDeleteProgram(program);
}

/*
 * Get information log from given program and throws runtime error with this log
 *
 * GLuint programToCheck - particular shader (i.e vertex shader) or whole shader program which failed
 * string& logMsg - A message which will be added to error string
 * void *parameterAccessFunc - ptr to function which returns parameters from objects (i.e glGetProgramiv)
 * void *informationLogFunc - ptr to function which return information log (i.e glGetProgramInfoLog)
 */
void ShaderProgram::throwErrorWithMsg(GLuint programToCheck, const string &logMsg,
                                      void (*parameterAccessFunc)(GLuint, GLenum, GLint *),
                                      void (*informationLogFunc)(GLuint, GLsizei, GLsizei *, GLchar *)) {
    GLint infoLogLength;
    GLchar* _infoLog;
    stringstream infoLog;

    parameterAccessFunc(programToCheck, GL_INFO_LOG_LENGTH, &infoLogLength);
    _infoLog = new GLchar[infoLogLength];
    informationLogFunc(programToCheck, infoLogLength, nullptr, _infoLog);
    infoLog << logMsg << _infoLog;
    delete [] _infoLog;

    throw runtime_error(infoLog.str());
}

