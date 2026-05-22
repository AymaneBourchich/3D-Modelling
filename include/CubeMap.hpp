#pragma once

#include <string>

class CubeMap
{
public:
    CubeMap(const std::string faces[6]);

    ~CubeMap();

    void bind() const;

private:
    unsigned int textureId;
};