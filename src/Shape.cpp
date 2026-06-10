#include "Shape.hpp"
#include <GL/glew.h>

Shape::Shape(Vertex *vertices, unsigned int vertexCount, const unsigned int *indices, unsigned int indexCount)
    : indexCount(indexCount)
{
    for (unsigned int i = 0; i < vertexCount; i++)
    {
        points.push_back(vertices[0].position);
        originalPoints.push_back(vertices[0].position);
    }

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texCoord));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, color));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
}

Shape::~Shape()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void Shape::draw() const
{
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}

void Shape::draw(const Shader &shader, const glm::mat4 model)
{
    shader.setModel(model);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    //updatePoints(model);
}

void Shape::updatePoints(const glm::mat4 model)
{
    for (size_t i = 0; i < originalPoints.size(); ++i) {
            points[i] = glm::vec3(model * glm::vec4(originalPoints[i], 1.0f));
        }
}

float Shape::minX()
{
    auto minX = std::min_element(points.begin(), points.end(), [](glm::vec3 point1, glm::vec3 point2)
                                 { return point1.x < point2.x; });
    return minX->x;
}

float Shape::minY()
{
    auto minY = std::min_element(points.begin(), points.end(), [](glm::vec3 point1, glm::vec3 point2)
                                 { return point1.y < point2.y; });
    return minY->y;
}

float Shape::minZ()
{
    auto minZ = std::min_element(points.begin(), points.end(), [](glm::vec3 point1, glm::vec3 point2)
                                 { return point1.z < point2.z; });

    return minZ->z;
}

float Shape::maxX()
{
    auto minX = std::max_element(points.begin(), points.end(), [](glm::vec3 point1, glm::vec3 point2)
                                 { return point1.x < point2.x; });

    return minX->x;
}

float Shape::maxY()
{
    auto minY = std::max_element(points.begin(), points.end(), [](glm::vec3 point1, glm::vec3 point2)
                                 { return point1.y < point2.y; });

    return minY->y;
}

float Shape::maxZ()
{
    auto minZ = std::max_element(points.begin(), points.end(), [](glm::vec3 point1, glm::vec3 point2)
                                 { return point1.z < point2.z; });

    return minZ->z;
}

glm::vec3 Shape::bottomLeft()
{
    float minX = this->minX();
    float minY = this->minY();
    auto bottomLeft = std::find_if(points.begin(), points.end(), [minX, minY](glm::vec3 point) {
        return point.x == minX && point.y == minY;
    });

    return *bottomLeft;
}

glm::vec3 Shape::bottomRight()
{
    float maxX = this->maxX();
    float minY = this->minY();
    auto bottomRight = std::find_if(points.begin(), points.end(), [maxX, minY](glm::vec3 point) {
        return point.x == maxX && point.y == minY;
    });

    return *bottomRight;
}

glm::vec3 Shape::topLeft()
{
    float minX = this->minX();
    float maxY = this->maxY();
    auto topLeft = std::find_if(points.begin(), points.end(), [minX, maxY](glm::vec3 point) {
        return point.x == minX && point.y == maxY;
    });

    return *topLeft;
}

glm::vec3 Shape::topRight()
{
    float minX = this->minX();
    float maxY = this->maxY();
    auto topRight = std::find_if(points.begin(), points.end(), [minX, maxY](glm::vec3 point) {
        return point.x == minX && point.y == maxY;
    });

    return *topRight;
}