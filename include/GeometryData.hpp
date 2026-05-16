#include "Vertex.hpp"
float CUBE_VERTICES[] =
    {
        // Front
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,

        // Back
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f
    };

unsigned int CUBE_INDICES[] =
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
        1, 0, 4
    };

const float TRI_VERTCES[] =
    {
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };

const unsigned int TRI_INDICES[] =
    {0, 1, 2};

namespace Colors
{
    inline constexpr glm::vec4 white      = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    inline constexpr glm::vec4 black      = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    inline constexpr glm::vec4 red        = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    inline constexpr glm::vec4 green      = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    inline constexpr glm::vec4 blue       = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

    inline constexpr glm::vec4 yellow     = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
    inline constexpr glm::vec4 cyan       = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
    inline constexpr glm::vec4 magenta    = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);

    inline constexpr glm::vec4 orange     = glm::vec4(1.0f, 0.5f, 0.0f, 1.0f);
    inline constexpr glm::vec4 purple     = glm::vec4(0.5f, 0.0f, 0.5f, 1.0f);
    inline constexpr glm::vec4 pink       = glm::vec4(1.0f, 0.4f, 0.7f, 1.0f);

    inline constexpr glm::vec4 gray       = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
    inline constexpr glm::vec4 darkGray   = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
    inline constexpr glm::vec4 lightGray  = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);

    inline constexpr glm::vec4 skyBlue    = glm::vec4(0.53f, 0.81f, 0.92f, 1.0f);
    inline constexpr glm::vec4 navy       = glm::vec4(0.0f, 0.0f, 0.5f, 1.0f);

    inline constexpr glm::vec4 lime       = glm::vec4(0.75f, 1.0f, 0.0f, 1.0f);
    inline constexpr glm::vec4 teal       = glm::vec4(0.0f, 0.5f, 0.5f, 1.0f);
}

Vertex vertices[] =
{
    { {0.0f, 0.5f, 0.0f} },
    { {0.5f, -0.5f, 0.0f} },
    { {-0.5f, -0.5f, 0.0f} }
};