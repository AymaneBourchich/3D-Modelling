#include <glm/glm.hpp>
#include "Vertex.hpp"
#pragma once
struct DirLight
{
    DirLight(glm::vec3 direction) : direction(direction) {}

    DirLight(glm::vec3 direction, Light light)
        : direction(direction), ambient(light.ambient), diffuse(light.diffuse), specular(light.specular)
    {
    }
    glm::vec3 direction = glm::vec3(0.0f, -1.0f, 1.0f);

    glm::vec3 ambient = glm::vec3(0.15f);
    glm::vec3 diffuse = glm::vec3(0.80f);
    glm::vec3 specular = glm::vec3(0.40f);
};

struct PointLight
{
    PointLight(glm::vec3 position) : position(position) {}
    PointLight(glm::vec3 position, Light light) : position(position), ambient(light.ambient), diffuse(light.diffuse), specular(light.specular) {}

    glm::vec3 position;

    float constant = 1.0;
    float linear = 0.7;
    float quadratic = 1.8;

    glm::vec3 ambient = glm::vec3(0.02f);
    glm::vec3 diffuse = glm::vec3(0.70f);
    glm::vec3 specular = glm::vec3(1.00f);
};

struct SpotLight
{
    SpotLight(glm::vec3 position, glm::vec3 direction) : position(position), direction(direction) {}
    SpotLight(glm::vec3 position, glm::vec3 direction, Light light) : position(position), direction(direction), ambient(light.ambient), diffuse(light.diffuse), specular(light.specular) {}
    glm::vec3 position;
    glm::vec3 direction;

    float cutOff = glm::cos(glm::radians(12.5f));
    float outerCutOff = glm::cos(glm::radians(17.5f));

    float constant = 1.0;
    float linear = 0.7;
    float quadratic = 1.8;

    glm::vec3 ambient = glm::vec3(0.00f);
    glm::vec3 diffuse = glm::vec3(1.00f);
    glm::vec3 specular = glm::vec3(1.20f);
};

DirLight DEFAULT_DIR = DirLight(glm::vec3(0.0f, -1.0f, 0.0f));
PointLight DEFAULT_POINT = PointLight(glm::vec3(0.0f, 2.0f, 0.0f)); //draw a cube in that position