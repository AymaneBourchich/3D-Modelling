// main.cpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>
#include "Camera.hpp"
#include "Shader.hpp"
#include "CubeMap.hpp"
#include "Model.hpp"

#include <math.h>

std::array<std::string, 6> getCubemap(std::string folderName);
static void mouseCallback([[maybe_unused]] GLFWwindow *window, double mouseX, double mouseY);
static void processInput(GLFWwindow *window);

GLFWwindow *globalWindow = nullptr;
static Camera *globalCamera = nullptr;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor *primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(primaryMonitor);

    globalWindow = glfwCreateWindow(mode->width, mode->height, "FPS Camera", primaryMonitor, nullptr);
    glfwMakeContextCurrent(globalWindow);
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cout << "CRITICAL: GLEW failed to initialize!" << std::endl;
        return -1;
    }

    glViewport(0, 0, mode->width, mode->height);


    glfwSetCursorPosCallback(globalWindow, mouseCallback);
    glfwSetInputMode(globalWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);

    float prevTime = 0.0f;
    Shader modelShader("shaders/model.vert", "shaders/model.frag");
    Model model("backpack/backpack.obj");
    Camera camera;
    globalCamera = &camera;
    while (!glfwWindowShouldClose(globalWindow))
    {
        processInput(globalWindow);

        float currentTime = glfwGetTime();
        float elapstedTime = currentTime - prevTime;
        prevTime = currentTime;

        glm::mat4 VIEW_MATRIX = camera.getViewMatrix();
        camera.processKeyboardInput(elapstedTime);
        glm::mat4 PROJ_MATRIX = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //-----------------------------------------//
        modelShader.use();

        modelShader.setMVP(glm::mat4(1.0f), VIEW_MATRIX, PROJ_MATRIX);
        modelShader.setModel(glm::rotate(glm::mat4(1.0f), currentTime, glm::vec3(0, 1, 0)));
        model.Draw(modelShader);
        //------------------------------------------------------//

        glfwSwapBuffers(globalWindow);
        glfwPollEvents();
    }

    glfwDestroyWindow(globalWindow);

    glfwTerminate();

    return 0;
}

std::array<std::string, 6> getCubemap(std::string folderName)
{
    return {
        "cubemaps/" + folderName + "/right.jpg",
        "cubemaps/" + folderName + "/left.jpg",
        "cubemaps/" + folderName + "/top.jpg",
        "cubemaps/" + folderName + "/bottom.jpg",
        "cubemaps/" + folderName + "/front.jpg",
        "cubemaps/" + folderName + "/back.jpg"};
}

static void mouseCallback([[maybe_unused]] GLFWwindow *window, double mouseX, double mouseY)
{
    globalCamera->processMouseInput(mouseX, mouseY);
}
static void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

