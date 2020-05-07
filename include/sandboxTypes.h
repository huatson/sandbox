#ifndef __SANDBOX_TYPES__
#define __SANDBOX_TYPES__

#define SRC_WIDTH   800
#define SRC_HEIGHT  600
#define LOG_SIZE    512

// GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


struct FShaderData
{
public:
    FShaderData(int _t)
        : type(_t), shader(0){}
    FShaderData() 
        : type(0), shader(0){}
    ~FShaderData() {}
    
    int type;
    GLuint shader;
};

struct FLinkShaderData
{
public:
    FLinkShaderData()
        : vertexdata(FShaderData()), fragmentdata(FShaderData()), shaderprogram(0), VAO(0), VBO(0), EBO(0) {}
    FLinkShaderData(FShaderData &v, FShaderData &f)
        : vertexdata(v), fragmentdata(f), shaderprogram(0), VAO(0), VBO(0), EBO(0) {}
    ~FLinkShaderData() {}

    FShaderData vertexdata;
    FShaderData fragmentdata;
    GLuint shaderprogram;
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
};

#endif  //__SANDBOX_TYPES__