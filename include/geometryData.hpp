#include <vector>
#include "Vertex.hpp"
#include <glm/glm.hpp>

std::vector<Vertex> triVertices = {
    {glm::vec3(-0.5f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    {glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
    {glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 1.0f)},

};

std::vector<unsigned int> triIndices = {0, 1, 2};

