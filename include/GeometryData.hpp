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