// main.cpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include "Camera.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include "Shape.hpp"
#include "GeometryData.hpp"
#include "CubeMap.hpp"
#include "Light.hpp"
#include "models.hpp"
#include "MaterialData.hpp"
#include <math.h>

std::array<std::string, 6> getCubemap(std::string folderName);
static void mouseCallback([[maybe_unused]] GLFWwindow *window, double mouseX, double mouseY);
static void processInput(GLFWwindow *window);
void setDirLight(Shader &shader, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
void setPointLight(Shader &shader, glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
void setSpotLight(Shader &shader, glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

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
    glewInit();
    glViewport(0, 0, mode->width, mode->height);

    glEnable(GL_DEPTH_TEST);

    Camera camera;
    globalCamera = &camera;

    Shader basicShader("shaders/basic.vert", "shaders/basic.frag");
    Shader texShader("shaders/texture.vert", "shaders/texture.frag");
    Shader skyBoxShader("shaders/cubemap.vert", "shaders/cubemap.frag");
    Shader lightShader("shaders/light.vert", "shaders/light.frag");
    Shader materialShader("shaders/material.vert", "shaders/material.frag");

    Texture texBox("textures/box.jpg");
    Texture texBoxSpec("textures/boxSpec.jpg");
    Texture texSoil("textures/soil.jpg");
    Texture texFloor("textures/metal.jpg");
    Texture texConcrete("textures/rebar.jpg");

    CubeMap cubeMap(getCubemap("redNebula/1"));

    Shape triangle(Triangle::VERTICES, Triangle::VERTEX_COUNT, Triangle::INDICES, Triangle::INDEX_COUNT);
    Shape quad(Quad::VERTICES, Quad::VERTEX_COUNT, Quad::INDICES, Quad::INDEX_COUNT);
    Shape cube(Cube::VERTICES, Cube::VERTEX_COUNT, Cube::INDICES, Cube::INDEX_COUNT);

    glfwSetCursorPosCallback(globalWindow, mouseCallback);
    glfwSetInputMode(globalWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    float prevTime = 0.0f;

    while (!glfwWindowShouldClose(globalWindow))
    {
        float VAR = glfwGetTime();
        float deltaTime = VAR - prevTime;
        prevTime = VAR;
        processInput(globalWindow);

        camera.processKeyboardInput(deltaTime);

        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 VIEW = camera.getViewMatrix();
        glm::mat4 PROJ = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

        //-----------------------------------------//
        skyBoxShader.use();
        glDepthMask(GL_FALSE);
        skyBoxShader.setMVP(IDENTITY, glm::mat4(glm::mat3(VIEW)), PROJ);
        cubeMap.bind();
        cube.draw();
        glDepthMask(GL_TRUE);

        //-----------------------------------------//
        materialShader.use();
        materialShader.setMaterial(materials[MaterialName::CHROME]);

        materialShader.setMVP(IDENTITY, VIEW, PROJ);

        cube.draw();


        glfwSwapBuffers(globalWindow);
        glfwPollEvents();
    }

    glfwDestroyWindow(globalWindow);

    glfwTerminate();

    return 0;
}
void setDirLight(Shader &shader, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
    shader.setVec3("dirLight.direction", direction);
    shader.setVec3("dirLight.ambient", ambient);
    shader.setVec3("dirLight.diffuse", diffuse);
    shader.setVec3("dirLight.specular", specular);
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