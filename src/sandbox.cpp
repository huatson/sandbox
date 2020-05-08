#include "sandbox.h"

using namespace std;

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}


int main()
{
    cout << "Init Engine\n";
    //Engine
    SandboxEngine *engine = new SandboxEngine();
    if (!engine)
    {
        cerr << "\nFailed\n";
        return EXIT_FAILURE;
    }
    // glfw: initialize and configure
    cout << "GLFW";
    if (!engine->initialize(3, 3))
    {
        cerr << "\tFailed\n";
        glfwTerminate();
        return EXIT_FAILURE;
    }
    // glfw window creation
    cout << "VPort";
    GLFWwindow *window = engine->createWindow(SRC_WIDTH, SRC_HEIGHT, "Sandbox Engine");
    if (!window)
    {
        cerr << "\tFAILED\n";
        glfwTerminate();
        return EXIT_FAILURE;
    }
    // glad: load all OpenGL function pointers
    cout << "GLAD";
    if (!engine->validateGLAD(SRC_WIDTH, SRC_HEIGHT))
    {
        cerr << "\tFAILED\n";
        glfwTerminate();
        return EXIT_FAILURE;
    }
    // build and compile our shader program
    cout << "Shaders";
    SandboxShader *shader = new SandboxShader();
    if(!shader || !shader->build("build/basic_vshader.vs", "build/basic_fshader.fs"))
    {
        cerr << "\tFAILED\n";
        glfwTerminate();
        return EXIT_FAILURE;
    }
    // set up vertex data (and buffer(s)) and configure vertex attributes
    engine->generateBuffers();

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        engine->updateEngine(window, shader);
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return EXIT_SUCCESS;
}
