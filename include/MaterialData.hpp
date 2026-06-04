#pragma once
#include <glm/glm.hpp>
#include <map>
#include <string>
#include <glm/vec3.hpp>
#include "Light.hpp"

enum class MaterialName {
    EMERALD,
    JADE,
    OBSIDIAN,
    PEARL,
    RUBY,
    TURQUOISE,
    BRASS,
    BRONZE,
    CHROME,
    COPPER,
    GOLD,
    SILVER,
    BLACK_PLASTIC,
    CYAN_PLASTIC,
    GREEN_PLASTIC,
    RED_PLASTIC,
    WHITE_PLASTIC,
    YELLOW_PLASTIC,
    BLACK_RUBBER,
    CYAN_RUBBER,
    GREEN_RUBBER,
    RED_RUBBER,
    WHITE_RUBBER,
    YELLOW_RUBBER
};

std::map<MaterialName, Material> materials = {
    {
        MaterialName::EMERALD,
        {
            glm::vec3(0.0215f, 0.1745f, 0.0215f),
            glm::vec3(0.07568f, 0.61424f, 0.07568f),
            glm::vec3(0.633f, 0.727811f, 0.633f),
            0.6f
        }
    },
    {
        MaterialName::JADE,
        {
            glm::vec3(0.135f, 0.2225f, 0.1575f),
            glm::vec3(0.54f, 0.89f, 0.63f),
            glm::vec3(0.316228f, 0.316228f, 0.316228f),
            0.1f
        }
    },
    {
        MaterialName::OBSIDIAN,
        {
            glm::vec3(0.05375f, 0.05f, 0.06625f),
            glm::vec3(0.18275f, 0.17f, 0.22525f),
            glm::vec3(0.332741f, 0.328634f, 0.346435f),
            0.3f
        }
    },
    {
        MaterialName::PEARL,
        {
            glm::vec3(0.25f, 0.20725f, 0.20725f),
            glm::vec3(1.0f, 0.829f, 0.829f),
            glm::vec3(0.296648f, 0.296648f, 0.296648f),
            0.088f
        }
    },
    {
        MaterialName::RUBY,
        {
            glm::vec3(0.1745f, 0.01175f, 0.01175f),
            glm::vec3(0.61424f, 0.04136f, 0.04136f),
            glm::vec3(0.727811f, 0.626959f, 0.626959f),
            0.6f
        }
    },
    {
        MaterialName::TURQUOISE,
        {
            glm::vec3(0.1f, 0.18725f, 0.1745f),
            glm::vec3(0.396f, 0.74151f, 0.69102f),
            glm::vec3(0.297254f, 0.30829f, 0.306678f),
            0.1f
        }
    },
    {
        MaterialName::BRASS,
        {
            glm::vec3(0.329412f, 0.223529f, 0.027451f),
            glm::vec3(0.780392f, 0.568627f, 0.113725f),
            glm::vec3(0.992157f, 0.941176f, 0.807843f),
            0.21794872f
        }
    },
    {
        MaterialName::BRONZE,
        {
            glm::vec3(0.2125f, 0.1275f, 0.054f),
            glm::vec3(0.714f, 0.4284f, 0.18144f),
            glm::vec3(0.393548f, 0.271906f, 0.166721f),
            0.2f
        }
    },
    {
        MaterialName::CHROME,
        {
            glm::vec3(0.25f, 0.25f, 0.25f),
            glm::vec3(0.4f, 0.4f, 0.4f),
            glm::vec3(0.774597f, 0.774597f, 0.774597f),
            0.6f
        }
    },
    {
        MaterialName::COPPER,
        {
            glm::vec3(0.19125f, 0.0735f, 0.0225f),
            glm::vec3(0.7038f, 0.27048f, 0.0828f),
            glm::vec3(0.256777f, 0.137622f, 0.086014f),
            0.1f
        }
    },
    {
        MaterialName::GOLD,
        {
            glm::vec3(0.24725f, 0.1995f, 0.0745f),
            glm::vec3(0.75164f, 0.60648f, 0.22648f),
            glm::vec3(0.628281f, 0.555802f, 0.366065f),
            0.4f
        }
    },
    {
        MaterialName::SILVER,
        {
            glm::vec3(0.19225f, 0.19225f, 0.19225f),
            glm::vec3(0.50754f, 0.50754f, 0.50754f),
            glm::vec3(0.508273f, 0.508273f, 0.508273f),
            0.4f
        }
    },
    {
        MaterialName::BLACK_PLASTIC,
        {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.01f, 0.01f, 0.01f),
            glm::vec3(0.5f, 0.5f, 0.5f),
            0.25f
        }
    },
    {
        MaterialName::CYAN_PLASTIC,
        {
            glm::vec3(0.0f, 0.1f, 0.06f),
            glm::vec3(0.0f, 0.50980392f, 0.50980392f),
            glm::vec3(0.50196078f, 0.50196078f, 0.50196078f),
            0.25f
        }
    },
    {
        MaterialName::GREEN_PLASTIC,
        {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.1f, 0.35f, 0.1f),
            glm::vec3(0.45f, 0.55f, 0.45f),
            0.25f
        }
    },
    {
        MaterialName::RED_PLASTIC,
        {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.5f, 0.0f, 0.0f),
            glm::vec3(0.7f, 0.6f, 0.6f),
            0.25f
        }
    },
    {
        MaterialName::WHITE_PLASTIC,
        {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.55f, 0.55f, 0.55f),
            glm::vec3(0.7f, 0.7f, 0.7f),
            0.25f
        }
    },
    {
        MaterialName::YELLOW_PLASTIC,
        {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.5f, 0.5f, 0.0f),
            glm::vec3(0.6f, 0.6f, 0.5f),
            0.25f
        }
    },
    {
        MaterialName::BLACK_RUBBER,
        {
            glm::vec3(0.02f, 0.02f, 0.02f),
            glm::vec3(0.01f, 0.01f, 0.01f),
            glm::vec3(0.4f, 0.4f, 0.4f),
            0.078125f
        }
    },
    {
        MaterialName::CYAN_RUBBER,
        {
            glm::vec3(0.0f, 0.05f, 0.05f),
            glm::vec3(0.4f, 0.5f, 0.5f),
            glm::vec3(0.04f, 0.7f, 0.7f),
            0.078125f
        }
    },
    {
        MaterialName::GREEN_RUBBER,
        {
            glm::vec3(0.0f, 0.05f, 0.0f),
            glm::vec3(0.4f, 0.5f, 0.4f),
            glm::vec3(0.04f, 0.7f, 0.04f),
            0.078125f
        }
    },
    {
        MaterialName::RED_RUBBER,
        {
            glm::vec3(0.05f, 0.0f, 0.0f),
            glm::vec3(0.5f, 0.4f, 0.4f),
            glm::vec3(0.7f, 0.04f, 0.04f),
            0.078125f
        }
    },
    {
        MaterialName::WHITE_RUBBER,
        {
            glm::vec3(0.05f, 0.05f, 0.05f),
            glm::vec3(0.5f, 0.5f, 0.5f),
            glm::vec3(0.7f, 0.7f, 0.7f),
            0.078125f
        }
    },
    {
        MaterialName::YELLOW_RUBBER,
        {
            glm::vec3(0.05f, 0.05f, 0.0f),
            glm::vec3(0.5f, 0.5f, 0.4f),
            glm::vec3(0.7f, 0.7f, 0.04f),
            0.078125f
        }
    }
};