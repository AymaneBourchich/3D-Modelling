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
#include "CubeMap.hpp"
#include "Light.hpp"
#include "models.hpp"
#include "MaterialData.hpp"
#include "LightData.hpp"
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

    Texture diffuseRockMap("textures/rock.jpg");
    Texture specularRockMap("textures/rock_spec.jpg");

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
        materialShader.setMaterial(materials[MaterialName::EMERALD]);
        materialShader.setMVP(IDENTITY, VIEW, PROJ);
        glm::mat4 lightSource = IDENTITY;
        translate(lightSource, DEFAULT_SPOT.position);
        rotate(lightSource, VAR, Y_AXIS);
        scale(lightSource, glm::vec3(0.5f, 0.5f, 0.5f));
        materialShader.setModel(lightSource);
        cube.draw();

        //--------------------------------------------//
        lightShader.use();
        lightShader.setVec3("viewPos", camera.position);

        lightShader.setDiffuseMap(diffuseRockMap);
        lightShader.setSpecularMap(specularRockMap);
        lightShader.setFloat("material.shininess", 8.0f);

        lightShader.setDirLight(DEFAULT_DIR);
        lightShader.setPointLight(DEFAULT_POINT);
        lightShader.setSpotLight(DEFAULT_SPOT);

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(300.0f));

        // Create the rotation matrix
        glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        // Combine them: Rotation * Scale
        // The scaling happens first, and the rotation is applied to the scaled object
        glm::mat4 model = rotate * scale;

        // Apply to your shader
        lightShader.setMVP(model, VIEW, PROJ);

        quad.draw();

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