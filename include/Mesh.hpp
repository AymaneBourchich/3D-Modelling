#pragma once

#include "Shape.hpp"

class Mesh
{
    Shape& shape;
    Shader& shader;
    void draw();
};