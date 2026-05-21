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
#include <vector>

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

inline void generateSphere(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, float radius, int stacks, int sectors)
{
    vertices.clear();
    indices.clear();

    float pi = 3.1415926f;

    for (int i = 0; i <= stacks; i++)
    {
        float v = pi * i / stacks;
        float y = cos(v);
        float r = sin(v);

        for (int j = 0; j <= sectors; j++)
        {
            float u = 2.0f * pi * j / sectors;

            float x = cos(u) * r;
            float z = sin(u) * r;

            Vertex vertex;
            vertex.position = glm::vec3(x, y, z) * radius;
            vertex.normal = glm::vec3(x, y, z);
            vertex.texCoord = glm::vec2((float)j / sectors, (float)i / stacks);
            vertex.color = Colors::white;

            vertices.push_back(vertex);
        }
    }

    for (int i = 0; i < stacks; i++)
    {
        for (int j = 0; j < sectors; j++)
        {
            int first = i * (sectors + 1) + j;
            int second = first + sectors + 1;

            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }
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

    Texture texFloor("textures/floor.jpg");
    Texture texHex("textures/hex.jpg");
    Texture texNebula("textures/nebula.jpg");

    std::vector<Vertex> sphereVertices;
    std::vector<unsigned int> sphereIndices;
    generateSphere(sphereVertices, sphereIndices, 1.0f, 32, 32);

    Shape sphere(shaderTex, sphereVertices.data(), sphereVertices.size(), sphereIndices.data(), sphereIndices.size());
    Shape triangle(shaderTex, Triangle::VERTICES, Triangle::VERTEX_COUNT, Triangle::INDICES, Triangle::INDEX_COUNT);
    Shape floor(shaderTex, Quad::VERTICES, Quad::VERTEX_COUNT, Quad::INDICES, Quad::INDEX_COUNT);
    Shape stick(shaderBasic, Quad::VERTICES, Quad::VERTEX_COUNT, Quad::INDICES, Quad::INDEX_COUNT);
    Shape lantern(shaderBasic, Cube::VERTICES, Cube::VERTEX_COUNT, Cube::INDICES, Cube::INDEX_COUNT);

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

        //-----------DRAWING FLOOR------------------/
        glm::mat4 floorModel = IDENTITY;
        floorModel = glm::translate(floorModel, glm::vec3(-1.0f, -2.0f, 0.0f));
        floorModel = glm::rotate(floorModel, glm::radians(90.0f), X_AXIS);
        floorModel = glm::scale(floorModel, glm::vec3(100.0f, 100.0f, 100.0f));

        floor.shader.use();
        texHex.bind();
        floor.shader.setInt("texture0", 0);
        glActiveTexture(GL_TEXTURE0);
        floor.shader.setRenderState(floorModel, view, proj);
        floor.draw();

        //---------------------------------------------/

        glm::mat4 lanternModel = IDENTITY;
        lanternModel = glm::translate(lanternModel, glm::vec3(-3.0f, 1.0f, -3.0f));
        lanternModel = glm::rotate(lanternModel, 2 * currentTime, -X_AXIS + Y_AXIS);
        lantern.shader.use();
        lantern.shader.setRenderState(lanternModel, view, proj, Colors::red);
        lantern.draw();

        //-------------------------------------------------//

        glm::mat4 stickModel = IDENTITY;
        stickModel = glm::translate(stickModel, 5 * sinf(currentTime) * X_AXIS);
        stickModel = glm::translate(stickModel, glm::vec3(0.0f, 0.25f, -0.5f));
        stickModel = glm::rotate(stickModel, 5 * currentTime, Y_AXIS);
        stickModel = glm::rotate(stickModel, glm::radians(90.0f), X_AXIS);
        stickModel = glm::scale(stickModel, glm::vec3(1.5f, 0.1f, 1.0f));
        stick.shader.use();
        stick.shader.setRenderState(stickModel, view, proj, Colors::darkGray);
        stick.draw();

        glfwSwapBuffers(globalWindow);
        glfwPollEvents();
    }

    glfwDestroyWindow(globalWindow);

    glfwTerminate();

    return 0;
}