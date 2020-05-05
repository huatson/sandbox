#ifndef __SANDBOX_ENGINE__
#define __SANDBOX_ENGINE__


// GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// engine types
#include "sandboxTypes.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

struct FShaderData
{
public:
    FShaderData(int _t)
        : type(_t) {}
    FShaderData() {}
    ~FShaderData() {}

    GLuint shader;
    int type;
    GLint success;
    GLchar infoLog[LOG_SIZE];
};

class SandboxEngine
{
public:
    SandboxEngine(){}
    ~SandboxEngine() {}

    //  process all input: query GLFW whether relevant keys are 
    //  pressed/released this frame and react accordingly
    void processInput(GLFWwindow *window);
    bool initialize(int mayor, int minor);
    GLFWwindow *createWindow(int width, int height, const char* title);
    bool validateGLAD(int viewport_width, int viewport_height);
    bool createShader(FShaderData &data);
    bool linkShaders(FShaderData &vertexdata, FShaderData &fragmentdata);


    // shaders
    const GLchar *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    const GLchar *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";
private:

    const float triangle_vertices[9] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
};

#endif  //__SANDBOX_ENGINE__