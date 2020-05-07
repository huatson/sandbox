#include "sandbox.h"

using namespace std;

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

bool SandboxEngine::initialize(int mayor, int minor)
{
    if (!glfwInit())
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

GLFWwindow *SandboxEngine::createWindow(int width, int height, const char *title)
{
    GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window)
        return nullptr;
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
    glGetShaderiv(data.shader, GL_COMPILE_STATUS, &success);
    //  if any, retrieve the error message
    if (!success)
    {
        glGetShaderInfoLog(data.shader, LOG_SIZE, NULL, infoLog);
        cerr << "FAILED\n" << infoLog << endl;
        return false;
    }
    cout << "\tOK " << (data.type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << endl;
    return true;
}

bool SandboxEngine::linkShaders(FLinkShaderData &data)
{
    // link shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, data.vertexdata.shader);
    glAttachShader(shaderProgram, data.fragmentdata.shader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, LOG_SIZE, NULL, infoLog);
        cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
    }
    //glDeleteShader(data.vertexdata.shader);
    //glDeleteShader(data.fragmentdata.shader);

    GLuint VBO, VAO;
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);

    //  (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer)
    //  color position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

     //  activate shader program
    glUseProgram(shaderProgram);

    //  update parame
    data.shaderprogram = shaderProgram;
    data.VAO = VAO;
    data.VBO = VBO;

    cout << "\tOK\n";
    return true;
}

void SandboxEngine::updateEngine(GLFWwindow *window, FLinkShaderData &linkdata)
{
    // input
    processInput(window);
    // render background
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    //  Update foreground
    glBindVertexArray(linkdata.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);


    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(window);
    glfwPollEvents();
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
    // build shaders
    cout << "Shaders";
    FShaderData vertexdata = FShaderData(GL_VERTEX_SHADER);
    FShaderData fragmentdata = FShaderData(GL_FRAGMENT_SHADER);
    if (!engine->createShader(vertexdata) || !engine->createShader(fragmentdata))
    {
        cerr << "\tFAILED\n";
        glfwTerminate();
        return EXIT_FAILURE;
    }
    FLinkShaderData linkdata = FLinkShaderData(vertexdata, fragmentdata);
    cout << "Links";
    if (!engine->linkShaders(linkdata))
    {
        cerr << "\tFAILED\n";
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        engine->updateEngine(window,linkdata);
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &linkdata.VAO);
    glDeleteBuffers(1, &linkdata.VBO);
    glDeleteBuffers(1, &linkdata.EBO);
    glDeleteProgram(linkdata.shaderprogram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}
