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
#include "MaterialData.hpp"
#include "LightData.hpp"
#include "models.hpp"
#include <math.h>

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

GLFWwindow *globalWindow = nullptr;
static Camera *globalCamera = nullptr;
static void mouseCallback([[maybe_unused]] GLFWwindow *window, double mouseX, double mouseY)
{
    globalCamera->processMouseInput(mouseX, mouseY);
}
static void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

inline glm::mat4 move(float x = 0, float y = 0, float z = 0)
{
    return glm::translate(IDENTITY, glm::vec3(x, y, z));
}

inline glm::mat4 rotate(float angle, glm::vec3 axis = Y_AXIS)
{
    return glm::rotate(IDENTITY, angle, axis);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    globalWindow = glfwCreateWindow(1280, 720, "FPS Camera", nullptr, nullptr);
    glfwMakeContextCurrent(globalWindow);
    glewExperimental = GL_TRUE;
    glewInit();
    glViewport(0, 0, 1280, 720);

    glEnable(GL_DEPTH_TEST);

    Camera camera;
    globalCamera = &camera;

    Shader shaderBasic("shaders/basic.vert", "shaders/basic.frag");
    Shader shaderTex("shaders/texture.vert", "shaders/texture.frag");
    Shader shaderMap("shaders/cubemap.vert", "shaders/cubemap.frag");
    Shader shaderLight("shaders/light.vert", "shaders/light.frag");

    Texture texBox("textures/box.jpg");
    Texture texBoxSpec("textures/boxSpec.jpg");
    Texture texSoil("textures/soil.jpg");
    Texture texFloor("textures/metal.jpg");
    Texture texConcrete("textures/rebar.jpg");

    CubeMap CubeMap(getCubemap("redSky"));

    Shape triangle(shaderTex, Triangle::VERTICES, Triangle::VERTEX_COUNT, Triangle::INDICES, Triangle::INDEX_COUNT);
    Shape floor(shaderLight, Quad::VERTICES, Quad::VERTEX_COUNT, Quad::INDICES, Quad::INDEX_COUNT);
    Shape skyBox(shaderLight, Cube::VERTICES, Cube::VERTEX_COUNT, Cube::INDICES, Cube::INDEX_COUNT);

    Shape sky(shaderMap, Cube::VERTICES, Cube::VERTEX_COUNT, Cube::INDICES, Cube::INDEX_COUNT);

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

        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);


        glm::vec3 SUN_POSITION = glm::vec3(0.0f, -13.0f, 25.0f);

        shaderLight.use();
        shaderLight.setVec3("light.direction", SUN_POSITION);
        shaderLight.setVec3("light.ambient", lights[LightName::SUNSET].ambient);
        shaderLight.setVec3("light.diffuse", lights[LightName::SUNSET].diffuse);
        shaderLight.setVec3("light.specular", lights[LightName::SUNSET].specular);

        shaderLight.setView(view);
        shaderLight.setProj(proj);

        float freq = 5.0f;


        float r = (sinf(freq * VAR) + 1.0f) * 0.5f;
        float g = (sinf(freq * VAR + 2.094f) + 1.0f) * 0.5f;
        float b = (sinf(freq * VAR + 4.188f) + 1.0f) * 0.5f;

        // Apply the new color

        shaderBasic.use();
        shaderBasic.setColor(glm::vec4(r, g, b, sinf(VAR)));
        shaderBasic.setView(view);
        shaderBasic.setProj(proj);

        //-----------------------------------------//
        shaderMap.use();
        glDepthMask(GL_FALSE);
        sky.shader.setMVP(IDENTITY, glm::mat4(glm::mat3(view)), proj);
        CubeMap.bind();
        sky.draw();
        glDepthMask(GL_TRUE);

        //-----------DRAWING FLOOR------------------/

        glfwSwapBuffers(globalWindow);
        glfwPollEvents();
    }

    glfwDestroyWindow(globalWindow);

    glfwTerminate();

    return 0;
}