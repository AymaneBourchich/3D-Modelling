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

namespace Quad
{
    // {x, y, z}, {nx, ny, nz}, {u, v}, {r, g, b, a}
    Vertex VERTICES[] =
    {
        {{-0.5f, -0.5f, 0.0f}, {}, {0.0f, 0.0f}, Colors::white},
        {{ 0.5f, -0.5f, 0.0f}, {}, {1.0f, 0.0f}, Colors::white},
        {{ 0.5f,  0.5f, 0.0f}, {}, {1.0f, 1.0f}, Colors::white},
        {{-0.5f,  0.5f, 0.0f}, {}, {0.0f, 1.0f}, Colors::white}
    };

    const unsigned int INDICES[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    const unsigned int VERTEX_COUNT = 4;
    const unsigned int INDEX_COUNT = 6;
}
namespace Cube
{
    // Each face is duplicated so normals are correct per face
    // {x, y, z}, {nx, ny, nz}, {u, v}, {r, g, b, a}

    Vertex VERTICES[] =
    {
        // Front (+Z)
        {{-0.5f, -0.5f,  0.5f}, {0, 0, 1}, {0, 0}, Colors::white},
        {{ 0.5f, -0.5f,  0.5f}, {0, 0, 1}, {1, 0}, Colors::white},
        {{ 0.5f,  0.5f,  0.5f}, {0, 0, 1}, {1, 1}, Colors::white},
        {{-0.5f,  0.5f,  0.5f}, {0, 0, 1}, {0, 1}, Colors::white},

        // Back (-Z)
        {{ 0.5f, -0.5f, -0.5f}, {0, 0, -1}, {0, 0}, Colors::white},
        {{-0.5f, -0.5f, -0.5f}, {0, 0, -1}, {1, 0}, Colors::white},
        {{-0.5f,  0.5f, -0.5f}, {0, 0, -1}, {1, 1}, Colors::white},
        {{ 0.5f,  0.5f, -0.5f}, {0, 0, -1}, {0, 1}, Colors::white},

        // Left (-X)
        {{-0.5f, -0.5f, -0.5f}, {-1, 0, 0}, {0, 0}, Colors::white},
        {{-0.5f, -0.5f,  0.5f}, {-1, 0, 0}, {1, 0}, Colors::white},
        {{-0.5f,  0.5f,  0.5f}, {-1, 0, 0}, {1, 1}, Colors::white},
        {{-0.5f,  0.5f, -0.5f}, {-1, 0, 0}, {0, 1}, Colors::white},

        // Right (+X)
        {{ 0.5f, -0.5f,  0.5f}, {1, 0, 0}, {0, 0}, Colors::white},
        {{ 0.5f, -0.5f, -0.5f}, {1, 0, 0}, {1, 0}, Colors::white},
        {{ 0.5f,  0.5f, -0.5f}, {1, 0, 0}, {1, 1}, Colors::white},
        {{ 0.5f,  0.5f,  0.5f}, {1, 0, 0}, {0, 1}, Colors::white},

        // Top (+Y)
        {{-0.5f,  0.5f,  0.5f}, {0, 1, 0}, {0, 0}, Colors::white},
        {{ 0.5f,  0.5f,  0.5f}, {0, 1, 0}, {1, 0}, Colors::white},
        {{ 0.5f,  0.5f, -0.5f}, {0, 1, 0}, {1, 1}, Colors::white},
        {{-0.5f,  0.5f, -0.5f}, {0, 1, 0}, {0, 1}, Colors::white},

        // Bottom (-Y)
        {{-0.5f, -0.5f, -0.5f}, {0, -1, 0}, {0, 0}, Colors::white},
        {{ 0.5f, -0.5f, -0.5f}, {0, -1, 0}, {1, 0}, Colors::white},
        {{ 0.5f, -0.5f,  0.5f}, {0, -1, 0}, {1, 1}, Colors::white},
        {{-0.5f, -0.5f,  0.5f}, {0, -1, 0}, {0, 1}, Colors::white},
    };

    const unsigned int INDICES[] =
    {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        8, 9, 10, 10, 11, 8,
        12, 13, 14, 14, 15, 12,
        16, 17, 18, 18, 19, 16,
        20, 21, 22, 22, 23, 20
    };

    const unsigned int VERTEX_COUNT = 24;
    const unsigned int INDEX_COUNT = 36;
}

float skyboxVertices[] =
{
    -1,  1, -1,
    -1, -1, -1,
     1, -1, -1,
     1, -1, -1,
     1,  1, -1,
    -1,  1, -1,

    -1, -1,  1,
    -1, -1, -1,
    -1,  1, -1,
    -1,  1, -1,
    -1,  1,  1,
    -1, -1,  1,

     1, -1, -1,
     1, -1,  1,
     1,  1,  1,
     1,  1,  1,
     1,  1, -1,
     1, -1, -1,

    -1, -1,  1,
    -1,  1,  1,
     1,  1,  1,
     1,  1,  1,
     1, -1,  1,
    -1, -1,  1,

    -1,  1, -1,
     1,  1, -1,
     1,  1,  1,
     1,  1,  1,
    -1,  1,  1,
    -1,  1, -1,

    -1, -1, -1,
    -1, -1,  1,
     1, -1, -1,
     1, -1, -1,
    -1, -1,  1,
     1, -1,  1
};