#ifndef __SANDBOX_ENGINE__
#define __SANDBOX_ENGINE__

// engine types
#include "sandboxTypes.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

class SandboxEngine
{
public:
    SandboxEngine() : success(0) {}
    ~SandboxEngine() {}

    //  process all input: query GLFW whether relevant keys are
    //  pressed/released this frame and react accordingly
    void processInput(GLFWwindow *window);
    bool initialize(int mayor, int minor);
    GLFWwindow *createWindow(int width, int height, const char *title);
    bool validateGLAD(int viewport_width, int viewport_height);
    bool createShader(FShaderData &data);
    bool linkShaders(FLinkShaderData &data);
    void updateEngine(GLFWwindow *window, FLinkShaderData &linkdata);

private:
    GLint success;
    GLchar infoLog[LOG_SIZE];
    // shaders
    const GLchar *vertexShaderSource = "#version 330 core\n"
                                       "layout (location = 0) in vec3 aPos;\n"
                                       "layout (location = 1) in vec3 aColor;\n"
                                       "out vec3 ourColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   gl_Position = vec4(aPos, 1.0);\n"
                                       "   ourColor = aColor;\n"
                                       "}\0";

    const GLchar *fragmentShaderSource = "#version 330 core\n"
                                         "out vec4 FragColor;\n"
                                         "in vec3 ourColor;\n"
                                         "void main()\n"
                                         "{\n"
                                         "   FragColor = vec4(ourColor, 1.0f);\n"
                                         "}\n\0";
    float triangle_vertices[18] = {
        // positions         // colors
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // top
    };
    GLuint indices[6] = {
        0, 1, 3,
        1, 2, 3};
};

#endif  //__SANDBOX_ENGINE__