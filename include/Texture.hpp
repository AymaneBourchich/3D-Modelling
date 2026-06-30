#pragma once
#include "string"
struct Texture {
    unsigned int id;
    std::string type;
    std::string path;

    unsigned int loadFromFile(const std::string path, const std::string directory);

};  