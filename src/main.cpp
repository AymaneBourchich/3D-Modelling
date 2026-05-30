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
        float VAR = glfwGetTime();
        float deltaTime = VAR - prevTime;
        prevTime = VAR;
        processInput(globalWindow);

        camera.processKeyboardInput(deltaTime);

        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

        float WORLD_ROTATION_ANGLE = logf(VAR);
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
        shaderBasic.setColor(sinf(5 * VAR) * Colors::red);
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
        texFloor.bind(0);
        box.shader.setInt("material.specular", 1);
        texFloor.bind(1);
        box.shader.setFloat("material.shininess", 16.0f);

        glm::mat4 shift = glm::translate(IDENTITY, glm::vec3(0, 4, 0));
        // rotate(shift, currentTime, Y_AXIS);

        glm::mat4 arm1 = IDENTITY;

        scale(arm1, glm::vec3(4.0f, 1.0f, 1.0f));
        translate(arm1, -0.5f * X_AXIS);

        box.shader.setModel(shift * arm1);
        box.draw();

        glm::mat4 arm2 = IDENTITY;

        translate(arm2, glm::vec3(0, -0.5f, -0.5f));
        rotate(arm2, glm::radians(90.0f), Y_AXIS);
        translate(arm2, glm::vec3(0, 0.5f, 0.5f));

        box.shader.setModel(shift * arm2 * arm1);
        box.draw();

        glm::mat4 arm3 = IDENTITY;
        translate(arm3, glm::vec3(5.0f, -0.0f, 0.0f));
        box.shader.setModel(shift * arm3 * arm1);
        box.draw();

        glm::mat4 arm4 = IDENTITY;
        translate(arm4, glm::vec3(0.0f, -0.0f, -4.0f));
        box.shader.setModel(shift * arm4 * arm2 * arm1);
        box.draw();

        glm::mat4 column1 = IDENTITY;

        translate(column1, glm::vec3(-4.0f, 0.5f, 0.0f));
        rotate(column1, glm::radians(90.0f), -Z_AXIS);
        translate(column1, glm::vec3(4.0f, -0.5f, 0.0f));
        box.shader.setModel(shift * column1 * arm1);
        box.draw();

        glm::mat4 column2 = IDENTITY;
        translate(column2, glm::vec3(1.0f, 0.5f, -0.5f));
        rotate(column2, glm::radians(90.0f), Y_AXIS);
        translate(column2, glm::vec3(0.0f, -0.5f, -0.5f));
        box.shader.setModel(shift * column2 * column1 * arm1);
        box.draw();

        glm::mat4 column3 = IDENTITY;
        translate(column3, glm::vec3(9.0f, -0.0f, -0.0f));
        box.shader.setModel(shift * column3 * column1 * arm1);
        box.draw();

        glm::mat4 column4 = IDENTITY;
        translate(column4, glm::vec3(0.0f, -0.0f, -8.0f));
        box.shader.setModel(shift * column4 * column2 * column1 * arm1);
        box.draw();

        //-----------------------------------------///

        glm::mat4 laserBase = IDENTITY;

        translate(laserBase, glm::vec3(0.5f, 0.5f, 0.0f));

        rotate(laserBase, VAR, Y_AXIS);

        translate(laserBase, glm::vec3(0.0, 0.0, -4.0));
        scale(laserBase, glm::vec3(0.05f, 0.1f, 4.0f));
        translate(laserBase, glm::vec3(0.5, 0.5, 0.5));

        turret.shader.setModel(shift * laserBase);
        // turret.draw();

        turret.shader.setModel(move(4) * shift * laserBase);
        turret.draw();

        turret.shader.setModel(move(-4) * shift * laserBase);
        turret.draw();

        turret.shader.setModel(move(0, 0, 4) * shift * laserBase);
        turret.draw();

        turret.shader.setModel(move(0, 0, -4) * shift * laserBase);
        turret.draw();

        glfwSwapBuffers(globalWindow);
        glfwPollEvents();
    }

    glfwDestroyWindow(globalWindow);

    glfwTerminate();

    return 0;
}