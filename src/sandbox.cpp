#include "sandbox.h"

using namespace std;

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

bool SandboxEngine::initialize(int mayor, int minor)
{
    if(!glfwInit())
        return false;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    cout << "\tOK\n";
    return true;
}

void SandboxEngine::processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

GLFWwindow *SandboxEngine::createWindow(int width, int height, const char* title)
{
    GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);
    if(!window) return nullptr;
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    cout << "\tOK\n";
    return window;
}

bool SandboxEngine::validateGLAD(int viewport_width, int viewport_height)
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        return false;
    glViewport(0, 0, viewport_width, viewport_height);
    cout << "\tOK\n";
    return true;
}

bool SandboxEngine::createShader(FShaderData &data)
{
    //  Create a shader object, referenced by an ID
    data.shader = glCreateShader(data.type);
    //  Attach the shader source code to the shader object and compile the shader
    const GLchar *source = (data.type == GL_VERTEX_SHADER) ? vertexShaderSource : fragmentShaderSource;
    glShaderSource(data.shader, 1, &source, NULL);
    glCompileShader(data.shader);
    //  Checking for shader-compile-time errors
    glGetShaderiv(data.shader, GL_COMPILE_STATUS, &data.success);
    //  if any, retrieve the error message
    if (!data.success)
    {
        glGetShaderInfoLog(data.shader, LOG_SIZE, NULL, data.infoLog);
        cerr << "FAILED\n" << data.infoLog << endl;
        return false;
    }
    cout << "\tOK\n";
    return true;
}

bool SandboxEngine::linkShaders(FShaderData &vertexdata, FShaderData &fragmentdata)
{
    return true;
}

int main()
{
    cout << "Engine";
    //Engine
    SandboxEngine *engine = new SandboxEngine();
    if (!engine)
    {
        cerr << "\nFailed\n";
        return EXIT_FAILURE;
    }
    // glfw: initialize and configure
    cout << "GLFW";
    if(!engine->initialize(3,3))
    {
        cerr << "\tFailed\n";
        glfwTerminate();
        return EXIT_FAILURE;
    }
    // glfw window creation
    cout << "VPort";
    GLFWwindow *window = engine->createWindow(800,600,"Sandbox Engine");
    if(!window)
    {
        cerr << "\tFAILED\n";
        glfwTerminate();
        return EXIT_FAILURE;
    }
    // glad: load all OpenGL function pointers
    cout << "GLAD";
    if(!engine->validateGLAD(800,600))
    {
        cerr << "\tFAILED\n";
        glfwTerminate();
        return EXIT_FAILURE;
    }
        
    // build shaders
    cout << "Shaders";
    FShaderData vertexdata = FShaderData(GL_VERTEX_SHADER);
    FShaderData fragmentdata = FShaderData(GL_FRAGMENT_SHADER);
    if(!engine->createShader(vertexdata) || !engine->createShader(fragmentdata))
    {
        cerr << "\tFAILED\n";
        glfwTerminate();
        return EXIT_FAILURE;
    }

    //  main loop
    while (!glfwWindowShouldClose(window))
    {
        //  input
        engine->processInput(window);
        //  rendering background color
        glClearColor(0.2f, 0.3f, 0.3f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        //  check call events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    delete engine;
    return EXIT_SUCCESS;
}
