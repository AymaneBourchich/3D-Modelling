// Cube.cpp

#include "Cube.hpp"

#include <GL/glew.h>

Cube::Cube()
{
    float vertices[] =
    {
        // Front
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

        // Back
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f
    };

    unsigned int indices[] =
    {
        // Front
        0, 1, 2,
        2, 3, 0,

        // Right
        1, 5, 6,
        6, 2, 1,

        // Back
        5, 4, 7,
        7, 6, 5,

        // Left
        4, 0, 3,
        3, 7, 4,

        // Top
        3, 2, 6,
        6, 7, 3,

        // Bottom
        4, 5, 1,
        1, 0, 4
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

Cube::~Cube()
{
    glDeleteVertexArrays(1, &vao);

    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void Cube::draw() const
{
    glBindVertexArray(vao);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}