// Shape.hpp

#pragma once

#include "Shader.hpp"
#include "Vertex.hpp"

class Shape
{
public:
    Shape(Shader &shader, const Vertex* vertices, unsigned int vertexSize, const unsigned int *indices, unsigned int indexSize);

    ~Shape();

    void draw() const;

    Shader &shader;

private:
    unsigned int vao, vbo, ebo;
    unsigned int indexCount;
};

