#ifndef __SANDBOXSHADER_H__
#define __SANDBOXSHADER_H__

#include "sandboxTypes.h"

enum EShaderType
{
    EST_VERTEX,
    EST_FRAGMENT,
    EST_PROGRAM
};

class SandboxShader
{
public:
    // CTOR read and build shader
    SandboxShader();
    ~SandboxShader();

    bool build(const GLchar *vertexPath, const GLchar *fragmentPath);
    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

private:
    //ID
    GLuint shaderID;
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    std::stringstream vShaderStream;
    std::stringstream fShaderStream;
    GLuint vertex;
    GLuint fragment;
    int success;
    char infoLog[LOG_SIZE];

    // utility function for checking shader compilation/linking errors.
    bool checkCompileErrors(GLuint shader, EShaderType type);
};

#endif  //__SANDBOXSHADER_H__