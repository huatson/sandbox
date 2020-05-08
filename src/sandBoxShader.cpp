#include "sandboxShader.h"

SandboxShader::SandboxShader()
{
}

SandboxShader::~SandboxShader()
{
}

void SandboxShader::use()
{
    glUseProgram(shaderID); 
}

void SandboxShader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(shaderID, name.c_str()), (int)value); 
}

void SandboxShader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value); 
}

void SandboxShader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value); 
}

bool SandboxShader::checkCompileErrors(GLuint shader, EShaderType type)
{
    if(type != EShaderType::EST_PROGRAM)
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader,LOG_SIZE,NULL, infoLog);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            return false;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader,LOG_SIZE,NULL, infoLog);
            std::cerr << "ERROR::PROGRAM_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            return false;
        }
    }
    return true;
}

bool SandboxShader::build(const GLchar *vertexPath, const GLchar *fragmentPath)
{
    // 1. retrieve the vertex/fragment source code from filePath
    // ensure ifstream objects can throw exceptions
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        // read file’s buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::fstream::failure &e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        return false;
    }
    const GLchar *vShaderCode = vertexCode.c_str();
    const GLchar *fShaderCode = fragmentCode.c_str();
    //  2.Compile
    //  vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    if(!checkCompileErrors(vertex, EShaderType::EST_VERTEX)) return false;
    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    if(!checkCompileErrors(vertex, EShaderType::EST_FRAGMENT)) return false;
    // shader Program
    shaderID= glCreateProgram();
    glAttachShader(shaderID, vertex);
    glAttachShader(shaderID, fragment);
    glLinkProgram(shaderID);
    if(!checkCompileErrors(shaderID, EShaderType::EST_PROGRAM)) return false;
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    std::cout << "\tOK\n";
    return true;
}
