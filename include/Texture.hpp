#pragma once

#include <string>

class Texture
{
public:
    Texture(const std::string& filePath);

    ~Texture();

    void bind(int slot) const;

private:
    unsigned int textureId;
};