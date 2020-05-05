#ifndef __SANDBOX_ENGINE__
#define __SANDBOX_ENGINE__

// GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class SandboxEngine
{
public:
    SandboxEngine(){}

    //  process all input: query GLFW whether relevant keys are 
    //  pressed/released this frame and react accordingly
    void processInput(GLFWwindow *window);

};

#endif  //__SANDBOX_ENGINE__