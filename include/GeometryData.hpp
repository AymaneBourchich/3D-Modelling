#include "Vertex.hpp"
typedef glm::vec3 vec3;
typedef glm::vec2 vec2;
typedef glm::vec4 vec4;
namespace Colors
{
    inline constexpr glm::vec4 white = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    inline constexpr glm::vec4 black = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    inline constexpr glm::vec4 red = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    inline constexpr glm::vec4 green = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    inline constexpr glm::vec4 blue = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

    inline constexpr glm::vec4 yellow = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
    inline constexpr glm::vec4 cyan = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
    inline constexpr glm::vec4 magenta = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);

    inline constexpr glm::vec4 orange = glm::vec4(1.0f, 0.5f, 0.0f, 1.0f);
    inline constexpr glm::vec4 purple = glm::vec4(0.5f, 0.0f, 0.5f, 1.0f);
    inline constexpr glm::vec4 pink = glm::vec4(1.0f, 0.4f, 0.7f, 1.0f);

    inline constexpr glm::vec4 gray = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
    inline constexpr glm::vec4 darkGray = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
    inline constexpr glm::vec4 lightGray = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);

    inline constexpr glm::vec4 skyBlue = glm::vec4(0.53f, 0.81f, 0.92f, 1.0f);
    inline constexpr glm::vec4 navy = glm::vec4(0.0f, 0.0f, 0.5f, 1.0f);

    inline constexpr glm::vec4 lime = glm::vec4(0.75f, 1.0f, 0.0f, 1.0f);
    inline constexpr glm::vec4 teal = glm::vec4(0.0f, 0.5f, 0.5f, 1.0f);
}
namespace Cube
{
    // 8 vertices, only position set (others use defaults from Vertex)
    Vertex VERTICES[] =
        {
            // Front face
            {vec3(-0.5f, -0.5f, 0.5f)},
            {vec3(0.5f, -0.5f, 0.5f)},
            {vec3(0.5f, 0.5f, 0.5f)},
            {vec3(-0.5f, 0.5f, 0.5f)},

            // Back face
            {vec3(-0.5f, -0.5f, -0.5f)},
            {vec3(0.5f, -0.5f, -0.5f)},
            {vec3(0.5f, 0.5f, -0.5f)},
            {vec3(-0.5f, 0.5f, -0.5f)}};

    // 12 triangles (36 indices)
    const unsigned int INDICES[] =
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
            1, 0, 4};

    const unsigned int VERTEX_COUNT = 8;
    const unsigned int INDEX_COUNT = 36;
}

namespace Triangle
{
    // {x, y, z}, {nx, ny, nz}, {u, v}, {r, g, b, a}
    Vertex VERTICES[] =
{
    {{-0.5f, -0.5f, 0.0f}, {}, {0.0f, 0.0f}, Colors::white},
    {{ 0.5f, -0.5f, 0.0f}, {}, {1.0f, 0.0f}, Colors::white},
    {{ 0.5f,  0.5f, 0.0f}, {}, {1.0f, 1.0f}, Colors::white},
};

    const unsigned int INDICES[] =
        {0, 1, 2};

    const unsigned int VERTEX_COUNT = 3;
    const unsigned int INDEX_COUNT = 3;

}


