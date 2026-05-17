#pragma once

#include <string>

class Texture
{
public:
    Texture(const std::string& filePath);

    ~Texture();

    void bind() const;

private:
    unsigned int textureId;
};