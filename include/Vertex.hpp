#pragma once

#include <glm/glm.hpp>
#include <string>
#define MAX_BONE_INFLUENCE 4

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal   = glm::vec3(0.0f);
    glm::vec2 texCoord = glm::vec2(0.0f);
};

