#include "Game.h"
#include "../resources/shader/Shaders.h"

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "spdlog/spdlog.h"

bool StartGame()
{
    /* Initialize the library */
    if (!glfwInit())
        return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    auto monitor = glfwGetPrimaryMonitor();

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow *window = glfwCreateWindow(glfwGetVideoMode(monitor)->width, glfwGetVideoMode(monitor)->height, "Chess Analysis.", nullptr, nullptr);

    if (!window)
    {
        glfwTerminate();
        return false;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        return false;
    }

    // Set initial viewport to match framebuffer size
    int fbw = 0, fbh = 0;
    glfwGetFramebufferSize(window, &fbw, &fbh);
    glViewport(0, 0, fbw, fbh);

    // Keep viewport in sync on resize (important on macOS/Retina)
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int width, int height){
        glViewport(0, 0, width, height);
    });

    glClearColor(0.06f, 0.07f, 0.08f, 1.0f);

    /* Loop until the user closes the window */
    GameLoop(window);

    glfwTerminate();

    return true;
}

static void GameLoop(GLFWwindow* window)
{
    unsigned int vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    float positions[6] = {
        -0.5f, -0.5f,
         0.5f,  0.5f,
         0.5f, -0.5f
    };

    unsigned int triangleBuffer;
    glGenBuffers(1, &triangleBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, triangleBuffer);
    glBufferData(GL_ARRAY_BUFFER,  6 * sizeof(float), positions,  GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);

    const std::string shaderPath = std::string(PROJECT_SOURCE_DIR) + "/src/resources/shader/shaders/TriangleRed.shader";
    ShaderSources sources = ParseShader(shaderPath);

    unsigned int shader = CreateShader(sources.VertexSource, sources.FragmentSource);
    if (shader == 0)
    {
        spdlog::error("Failed to create shader program");
    }
    glUseProgram(shader);

    do
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    } while (!glfwWindowShouldClose(window));

    if (shader)
        glDeleteProgram(shader);
}
