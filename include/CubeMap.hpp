#pragma once

#include <string>
#include <array>

class CubeMap
{
public:
    CubeMap(const std::array<std::string, 6> faces);

    ~CubeMap();

    void bind() const;

private:
    unsigned int textureId;
};