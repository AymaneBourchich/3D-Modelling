#pragma once
#include "string"
class Texture
{

    public:
    Texture();
    Texture(const std::string path, const std::string directory, const std::string type);
    unsigned int id;
    std::string type;
    std::string path;

    unsigned int loadFromFile(const std::string path, const std::string directory);
    void bind();
};