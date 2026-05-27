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

    CubeMap CubeMap(getCubemap("greySky"));

    Shape triangle(shaderTex, Triangle::VERTICES, Triangle::VERTEX_COUNT, Triangle::INDICES, Triangle::INDEX_COUNT);
    Shape floor(shaderLight, Quad::VERTICES, Quad::VERTEX_COUNT, Quad::INDICES, Quad::INDEX_COUNT);
    Shape wall(shaderLight, Quad::VERTICES, Quad::VERTEX_COUNT, Quad::INDICES, Quad::INDEX_COUNT);
    Shape box(shaderLight, Cube::VERTICES, Cube::VERTEX_COUNT, Cube::INDICES, Cube::INDEX_COUNT);
    Shape tower(shaderLight, Cube::VERTICES, Cube::VERTEX_COUNT, Cube::INDICES, Cube::INDEX_COUNT);
    Shape blade(shaderLight, Cube::VERTICES, Cube::VERTEX_COUNT, Cube::INDICES, Cube::INDEX_COUNT);
    Shape turret(shaderBasic, Cube::VERTICES, Cube::VERTEX_COUNT, Cube::INDICES, Cube::INDEX_COUNT);

    Shape sky(shaderMap, Cube::VERTICES, Cube::VERTEX_COUNT, Cube::INDICES, Cube::INDEX_COUNT);

    glfwSetCursorPosCallback(globalWindow, mouseCallback);
    glfwSetInputMode(globalWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    float prevTime = 0.0f;

    while (!glfwWindowShouldClose(globalWindow))
    {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - prevTime;
        prevTime = currentTime;
        processInput(globalWindow);

        camera.processKeyboardInput(deltaTime);

        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

        float WORLD_ROTATION_ANGLE = logf(currentTime);
        glm::mat4 WORLD_ROTATION = glm::rotate(IDENTITY, WORLD_ROTATION_ANGLE, Y_AXIS);

        glm::vec3 SUN_POSITION = glm::vec3(0.0f, -13.0f, 25.0f);
        SUN_POSITION = glm::vec3(WORLD_ROTATION * glm::vec4(SUN_POSITION, 1.0f));

        shaderLight.use();
        shaderLight.setVec3("light.direction", SUN_POSITION);
        shaderLight.setVec3("light.ambient", lights[LightName::OVERCAST_DAY].ambient);
        shaderLight.setVec3("light.diffuse", lights[LightName::OVERCAST_DAY].diffuse);
        shaderLight.setVec3("light.specular", lights[LightName::OVERCAST_DAY].specular);

        shaderLight.setView(view);
        shaderLight.setProj(proj);

        shaderBasic.use();
        shaderBasic.setColor(sinf(5 * currentTime) * Colors::red);
        shaderBasic.setView(view);
        shaderBasic.setProj(proj);

        //-----------------------------------------//
        glDepthMask(GL_FALSE);
        glm::mat4 skyModel = WORLD_ROTATION;
        rotate(skyModel, glm::radians(90.0f), Y_AXIS);
        sky.shader.setMVP(skyModel, glm::mat4(glm::mat3(view)), proj);
        CubeMap.bind();
        sky.draw();
        glDepthMask(GL_TRUE);

        //-----------DRAWING FLOOR------------------/

        floor.shader.setInt("material.diffuse", 0);
        texFloor.bind(0);

        floor.shader.setInt("material.specular", 1);
        texFloor.bind(1);

        floor.shader.setFloat("material.shininess", 16.0f);

        glm::mat4 floorModel = IDENTITY;
        translate(floorModel, -0.5f * Y_AXIS);
        rotate(floorModel, glm::radians(90.0f), X_AXIS);
        scale(floorModel, glm::vec3(100.0f, 100.0f, 100.0f));
        floor.shader.setModel(floorModel);

        floor.draw();

        //--------------------------------------------------//
        box.shader.setInt("material.diffuse", 0);
        texBox.bind(0);
        box.shader.setInt("material.specular", 1);
        texBoxSpec.bind(1);
        box.shader.setFloat("material.shininess", 16.0f);

        glm::mat4 doorModel = IDENTITY;


        // translate(doorModel, -0.5f * X_AXIS);
        // rotate(doorModel, sinf(currentTime), Y_AXIS);
        // translate(doorModel, 0.5f * X_AXIS);

        translate(doorModel, -0.5f * Y_AXIS);
        scale(doorModel, glm::vec3(1.0f, 4.0f, 0.2f));
        translate(doorModel, 0.5f * Y_AXIS);

        box.shader.setModel(doorModel);
        box.draw();

        //-----------------------------//
        box.shader.setInt("material.diffuse", 0);
        texFloor.bind(0);
        box.shader.setInt("material.specular", 1);
        texFloor.bind(1);
        box.shader.setFloat("material.shininess", 16.0f);

        glm::mat4 handleModel = IDENTITY;

        translate(handleModel, glm::vec3(-0.9f, 2.0f, 0.2f));

        translate(handleModel, 0.5f * X_AXIS);
        scale(handleModel, glm::vec3(0.5f, 0.1f, 0.1f));
        translate(handleModel, 0.5f * X_AXIS);

        box.shader.setModel(handleModel);
        box.draw();

        glfwSwapBuffers(globalWindow);
        glfwPollEvents();
    }

    glfwDestroyWindow(globalWindow);

    glfwTerminate();

    return 0;
}