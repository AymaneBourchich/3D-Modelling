// main.cpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include "Camera.hpp"
#include "Shader.hpp"
#include "Shape.hpp"
#include "GeometryData.hpp"



GLFWwindow *globalWindow = nullptr;

static Camera *globalCamera = nullptr;

static void mouseCallback(GLFWwindow *window, double mouseX, double mouseY)
{
    globalCamera->processMouseInput(mouseX, mouseY);
}

static void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    globalWindow = glfwCreateWindow(1280, 720, "FPS Camera", nullptr, nullptr);

    if (globalWindow == nullptr)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(globalWindow);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW\n";
        return -1;
    }

    glViewport(0, 0, 1280, 720);

    glEnable(GL_DEPTH_TEST);

    Shader shader("shaders/basic.vert", "shaders/basic.frag");
    Camera camera;
    Shape cube(shader, CUBE_VERTICES, sizeof(CUBE_VERTICES), CUBE_INDICES, sizeof(CUBE_INDICES));
    Shape triangle(shader, TRI_VERTCES, sizeof(TRI_VERTCES), TRI_INDICES, sizeof(TRI_INDICES));

    globalCamera = &camera;

    glfwSetCursorPosCallback(globalWindow, mouseCallback);

    glfwSetInputMode(globalWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    float lastFrameTime = 0.0f;

    while (!glfwWindowShouldClose(globalWindow))
    {
        float currentFrameTime = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;
        processInput(globalWindow);

        camera.processKeyboardInput(deltaTime);

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

        cube.shader.use();
        cube.shader.setMat4("model", model);
        cube.shader.setMat4("view", view);
        cube.shader.setMat4("projection", projection);

        cube.draw();

        glfwSwapBuffers(globalWindow);

        glfwPollEvents();
    }

    glfwDestroyWindow(globalWindow);

    glfwTerminate();

    return 0;
}