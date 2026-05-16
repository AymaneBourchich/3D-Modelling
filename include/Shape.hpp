// Shape.hpp

#pragma once

#include "Shader.hpp"

class Shape
{
public:
    Shape(Shader &shader, const float *vertices, unsigned int vertexSize, const unsigned int *indices, unsigned int indexSize);

    ~Shape();

    void draw() const;

    Shader &shader;

private:
    unsigned int vao, vbo, ebo;
    unsigned int indexCount;
};

