// Shape.hpp

#pragma once

#include "Shader.hpp"
#include "Vertex.hpp"
#include <vector>
class Shape
{
public:
    Shape(Vertex *vertices, unsigned int vertexSize, const unsigned int *indices, unsigned int indexSize);

    ~Shape();

    void draw() const;
    void draw(const Shader &, const glm::mat4);

    float minX();
    float minY();
    float minZ();

    glm::vec3 topLeft();
    glm::vec3 topRight();
    glm::vec3 bottomLeft();
    glm::vec3 bottomRight();

    float maxX();
    float maxY();
    float maxZ();

private:
    void updatePoints(const glm::mat4 model);
    

    

    

    unsigned int vao, vbo, ebo;
    unsigned int indexCount;
    std::vector<glm::vec3> originalPoints;
    std::vector<glm::vec3> points;
};
