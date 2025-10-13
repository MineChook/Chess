#include "Game.h"

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "spdlog/spdlog.h"
#include "spdlog/fmt/bundled/core.h"

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int vertex_compiled;
    glGetShaderiv(id, GL_COMPILE_STATUS, &vertex_compiled);

    if (vertex_compiled != GL_TRUE)
    {
        int log_length = 0;
        char message[1024];
        glGetShaderInfoLog(id, 1024, &log_length, message);
        spdlog::error(message);
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glDetachShader(program, vs);
    glDetachShader(program, fs);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

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

    glClearColor(0.06f, 0.07f, 0.08f, 1.0f);

    /* Loop until the user closes the window */
    GameLoop(window);

    glfwTerminate();

    return true;
}

static void GameLoop(GLFWwindow* window)
{
    // Core profile requires a VAO
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


    std::string vertexShader =
        "#version 410 core\n"
        "\n"
        "layout(location = 0) in vec2 position;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(position, 0.0, 1.0);\n"
        "}\n";

    std::string fragmentShader =
            "#version 410 core\n"
            "layout(location = 0) out vec4 color;\n"
            "void main()\n"
            "{\n"
            "   color = vec4(1.0, 0.0, 0.0, 1.0);\n"
            "}\n";

    unsigned int shader = CreateShader(vertexShader, fragmentShader);
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
}
