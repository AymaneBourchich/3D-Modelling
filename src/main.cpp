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

void translate(glm::mat4 &model, glm::vec3 value)
{
    model = glm::translate(model, value);
}

void rotate(glm::mat4 &model, float angle, glm::vec3 axis)
{
    model = glm::rotate(model, angle, axis);
}

void rotateAroundPivot(glm::mat4 &model, float angle, glm::vec3 axis, glm::vec3 pivot)
{
    translate(model, pivot);
    rotate(model, angle, axis);
    translate(model, -pivot);
}

void scale(glm::mat4 &model, glm::vec3 value)
{
    model = glm::scale(model, value);
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

    Texture texFloor("textures/floor.jpg");
    Texture texBox("textures/box.jpg");
    Texture texBoxSpec("textures/boxSpec.jpg");
    Texture texSoil("textures/soil1.jpg");
    Texture texHex("textures/hex.jpg");
    Texture texNebula("textures/nebula.jpg");

    CubeMap CubeMap(getCubemap("blueSky"));

    Shape triangle(shaderTex, Triangle::VERTICES, Triangle::VERTEX_COUNT, Triangle::INDICES, Triangle::INDEX_COUNT);
    Shape floor(shaderTex, Quad::VERTICES, Quad::VERTEX_COUNT, Quad::INDICES, Quad::INDEX_COUNT);
    Shape stick(shaderBasic, Quad::VERTICES, Quad::VERTEX_COUNT, Quad::INDICES, Quad::INDEX_COUNT);
    Shape quad(shaderBasic, Quad::VERTICES, Quad::VERTEX_COUNT, Quad::INDICES, Quad::INDEX_COUNT);
    Shape box(shaderLight, Cube::VERTICES, Cube::VERTEX_COUNT, Cube::INDICES, Cube::INDEX_COUNT);

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

        //-----------------------------------------//
        glDepthMask(GL_FALSE);
        glm::mat4 skyModel = IDENTITY;

        float WORLD_ROTATION = 0;
        sky.shader.use();
        CubeMap.bind();
        rotate(skyModel, WORLD_ROTATION, Y_AXIS);
        rotate(skyModel, glm::radians(90.0f), Y_AXIS);
        sky.shader.setRenderState(skyModel, glm::mat4(glm::mat3(view)), proj);
        sky.draw();
        glDepthMask(GL_TRUE);

        glm::mat4 rotationMat = IDENTITY;
        rotate(rotationMat, WORLD_ROTATION, Y_AXIS);
        glm::vec3 SUN_POSITION = glm::vec3(0.0f, 10.0f, -25.0f);
        SUN_POSITION = glm::vec3(rotationMat * glm::vec4(SUN_POSITION, 1.0f));

        //-----------DRAWING FLOOR------------------/
        glm::mat4 floorModel = IDENTITY;
        rotate(floorModel, glm::radians(90.0f), X_AXIS);
        scale(floorModel, glm::vec3(100.0f, 100.0f, 100.0f));

        floor.shader.setRenderState(floorModel, view, proj);
        texSoil.bind();
        floor.shader.setInt("texture0", 0);
        glActiveTexture(GL_TEXTURE0);
        floor.draw();

        //----------------------------------------------//
        glm::mat4 cubeModel = IDENTITY;
        translate(cubeModel, Y_AXIS);
        box.shader.use();
        
        rotate(cubeModel, currentTime, Y_AXIS);
        box.shader.setModel(cubeModel);
        box.shader.setView(view);
        box.shader.setProj(proj);

        box.shader.setInt("material.diffuse", 1);
        glActiveTexture(GL_TEXTURE1);
        texBox.bind();

        box.shader.setInt("material.specular", 2);
        glActiveTexture(GL_TEXTURE2);
        texBoxSpec.bind();


        box.shader.setFloat("material.shininess", 32.0f);
        

        box.shader.setVec3("light.position", SUN_POSITION);
        box.shader.setVec3("light.ambient", lights[LightName::SUN_NOON].ambient);
        box.shader.setVec3("light.diffuse", lights[LightName::SUN_NOON].diffuse);
        box.shader.setVec3("light.specular", lights[LightName::SUN_NOON].specular);

        box.draw();

        //-------------------------------------------------//

        glm::mat4 stickModel = IDENTITY;
        translate(stickModel, glm::vec3(0.0f, 1.25f, -0.5f));
        rotate(stickModel, 3 * currentTime, Z_AXIS);
        scale(stickModel, glm::vec3(1.5f, 0.1f, 1.0f));
        stick.shader.setRenderState(stickModel, view, proj);
        // stick.draw();

        //-----------------------------------------------------//

        glm::mat4 quadModel = IDENTITY;

        glm::vec3 pivot = glm::vec3(-0.5f, 0.5f, 0.0f);

        translate(quadModel, 2.0f * Y_AXIS);
        rotateAroundPivot(quadModel, sinf(currentTime), Z_AXIS, pivot);

        quad.shader.setRenderState(quadModel, view, proj, Colors::red);
        // quad.draw();

        //-------------------------------------//

        glfwSwapBuffers(globalWindow);
        glfwPollEvents();
    }

    glfwDestroyWindow(globalWindow);

    glfwTerminate();

    return 0;
}