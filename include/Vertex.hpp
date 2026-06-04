#pragma once

#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal   = glm::vec3(0.0f);
    glm::vec2 texCoord = glm::vec2(0.0f);
    glm::vec4 color    = glm::vec4(0.0f);

    void setPosition(const glm::vec3& p) { position = p; }
    void setNormal(const glm::vec3& n)   { normal = n; }
    void setTexCoord(const glm::vec2& t) { texCoord = t; }
    void setColor(const glm::vec4& c)    { color = c; }
};

