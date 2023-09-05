#include <iostream>

#include "glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "opengl.h"
#include "window.h"
#include "utils.h"
#include "program.h"
#include "engine.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Constants
{
    namespace Window {
        static const int32_t WIDTH = 800;
        static const int32_t HEIGHT = 600;
        static const char* HEADER = "Test Window";
    }
}

void onResolutionChanged(GLFWwindow* window, int32_t width, int32_t height)
{
    //! TODO
    std::cout << "window size changed: " << width << "x" << height << std::endl;
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

int main()
{
    Engine engine;

    Window window(Constants::Window::WIDTH, Constants::Window::HEIGHT, Constants::Window::HEADER);

    if (!window.isValid())
    {
        std::cerr << "failed to initialize the window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(window.obj(), onResolutionChanged);
    glfwMakeContextCurrent(window.obj());

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };


//    float vertices[] = {
//        0.5f,  0.5f, 0.0f,  // top right
//        0.5f, -0.5f, 0.0f,  // bottom right
//       -0.5f, -0.5f, 0.0f,  // bottom left
//       -0.5f,  0.5f, 0.0f   // top left
//    };

    uint32_t VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int indices[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    std::string vertexShader;
    if (!Utils::readFile(std::string_view{"shaders/vertex.glsl"}, vertexShader))
    {
        return -1;
    }

    Shader vertexShaderCompiled(vertexShader, GL_VERTEX_SHADER);

    std::string fragmentShader;
    if (!Utils::readFile(std::string_view{"shaders/fragment.glsl"}, fragmentShader))
    {
        return -1;
    }

    Shader fragmentShaderCompiled(fragmentShader, GL_FRAGMENT_SHADER);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    Program program;
    program.attach(vertexShaderCompiled);
    program.attach(fragmentShaderCompiled);
    program.link();
    program.use();

    while(!glfwWindowShouldClose(window.obj()))
    {
        processInput(window.obj());

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window.obj());
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
