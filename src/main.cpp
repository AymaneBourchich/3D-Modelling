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

    // Shader shader("shaders/basic.vert", "shaders/basic.frag");
    Shader shader("shaders/texture.vert", "shaders/texture.frag");
    std::vector<Vertex> sphereVertices;
    std::vector<unsigned int> sphereIndices;

    generateSphere(sphereVertices, sphereIndices, 1.0f, 32, 32);

    Shape sphere(shader,
                 sphereVertices.data(),
                 sphereVertices.size(),
                 sphereIndices.data(),
                 sphereIndices.size());

    Camera camera;
    Texture textureFloor("textures/floor.jpg");
    Shape triangle(shader, Triangle::VERTICES, Triangle::VERTEX_COUNT, Triangle::INDICES, Triangle::INDEX_COUNT);
    Shape quad(shader, Quad::VERTICES, Quad::VERTEX_COUNT, Quad::INDICES, Quad::INDEX_COUNT);
    Shape cube(shader, Cube::VERTICES, Cube::VERTEX_COUNT, Cube::INDICES, Cube::INDEX_COUNT);

    globalCamera = &camera;

    glfwSetCursorPosCallback(globalWindow, mouseCallback);

    glfwSetInputMode(globalWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    float lastFrameTime = 0.0f;

    while (!glfwWindowShouldClose(globalWindow))
    {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;
        processInput(globalWindow);

        camera.processKeyboardInput(deltaTime);

        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(50.0f, 50.0f, 50.0f));


        shader.use();
        textureFloor.bind();
        shader.setInt("texture0", 0);
        glActiveTexture(GL_TEXTURE0);
        shader.setRenderState(model, view, proj, Colors::cyan);
        quad.draw();

        glfwSwapBuffers(globalWindow);
        glfwPollEvents();
    }

    glfwDestroyWindow(globalWindow);

    glfwTerminate();

    return 0;
}