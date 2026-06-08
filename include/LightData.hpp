#pragma once
#include <glm/glm.hpp>
#include <map>
#include <string>
#include <glm/vec3.hpp>
#include "Light.hpp"

enum class LightName
{
    SUN_NOON,
    SUNSET,
    SUNRISE,
    OVERCAST_DAY,
    INDOOR_TUNGSTEN,
    COOL_LED,
    NEON_BLUE,
    CANDLE,
    NIGHT_MOON,
    STUDIO_WHITE,
    RED_MOON
};

std::map<LightName, Light> lights = {
    {LightName::SUN_NOON,
     {glm::vec3(0.15f, 0.15f, 0.15f),
      glm::vec3(1.00f, 1.00f, 0.95f),
      glm::vec3(1.00f, 1.00f, 1.00f)}},
    {LightName::SUNSET,
     {glm::vec3(0.08f, 0.05f, 0.04f),
      glm::vec3(1.00f, 0.45f, 0.20f),
      glm::vec3(1.00f, 0.60f, 0.30f)}},
    {LightName::SUNRISE,
     {glm::vec3(0.07f, 0.05f, 0.06f),
      glm::vec3(1.00f, 0.40f, 0.25f),
      glm::vec3(0.90f, 0.55f, 0.35f)}},
    {LightName::OVERCAST_DAY,
     {glm::vec3(0.25f, 0.25f, 0.25f),
      glm::vec3(0.60f, 0.60f, 0.65f),
      glm::vec3(0.30f, 0.30f, 0.30f)}},
    {LightName::INDOOR_TUNGSTEN,
     {glm::vec3(0.05f, 0.05f, 0.05f),
      glm::vec3(1.00f, 0.85f, 0.60f),
      glm::vec3(1.00f, 0.90f, 0.70f)}},
    {LightName::COOL_LED,
     {glm::vec3(0.05f, 0.05f, 0.08f),
      glm::vec3(0.60f, 0.80f, 1.00f),
      glm::vec3(0.80f, 0.90f, 1.00f)}},
    {LightName::NEON_BLUE,
     {glm::vec3(0.03f, 0.03f, 0.08f),
      glm::vec3(0.20f, 0.50f, 1.00f),
      glm::vec3(0.50f, 0.70f, 1.00f)}},
    {LightName::CANDLE,
     {glm::vec3(0.02f, 0.01f, 0.01f),
      glm::vec3(1.00f, 0.40f, 0.10f),
      glm::vec3(1.00f, 0.50f, 0.20f)}},
    {LightName::NIGHT_MOON,
     {glm::vec3(0.02f, 0.02f, 0.03f),
      glm::vec3(0.15f, 0.18f, 0.25f),
      glm::vec3(0.30f, 0.30f, 0.35f)}},
    {LightName::STUDIO_WHITE,
     {glm::vec3(0.00f, 0.00f, 0.00f),
      glm::vec3(0.00f, 0.50f, 0.50f),
      glm::vec3(0.20f, 0.20f, 0.20f)}},
    {LightName::RED_MOON,
     {glm::vec3(0.02f, 0.001f, 0.001f),
      glm::vec3(0.2f, 0.02f, 0.02f),
      glm::vec3(0.2f, 0.2f, 0.2f)}}};

const glm::vec3 POSITIONS[7] = {
    glm::vec3(-1, 1, -1),
    glm::vec3(-4, 1, -1),
    glm::vec3(-2, 1, 1),
    glm::vec3(-1.5, 1, 2),
    glm::vec3(3, 1, 2),
    glm::vec3(3, 1, -2),
    glm::vec3(2, 1, -4),

};
DirLight DEFAULT_DIR = DirLight(glm::vec3(0.0f, -1.0f, 0.0f), lights[LightName::RED_MOON]);
PointLight DEFAULT_POINT = PointLight(glm::vec3(0.0f, 1.0f, 0.0f), lights[LightName::STUDIO_WHITE]);
SpotLight DEFAULT_SPOT = SpotLight(glm::vec3(-5.0f, 1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), lights[LightName::STUDIO_WHITE]);