#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <GL/glew.h>
#include <iostream>

unsigned int Texture::loadFromFile(const std::string path, const std::string directory)
{
    std::string filename = std::string(path);
    filename = directory + '/' + filename;
    std::cout << filename + "------------" << std::endl;
    unsigned int textureID;
    glGenTextures(1, &textureID);

    stbi_set_flip_vertically_on_load(true); // must match aiProcess_FlipUVs

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

    if (data)
    {
        GLenum format = GL_RGB; // safe default, was uninitialized before
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        GLenum err = glGetError();
        if (err != GL_NO_ERROR)
            std::cout << "glTexImage2D error: 0x" << std::hex << err << std::dec << std::endl;


        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // avoid row-padding issues on RGB textures
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "FAILED to load texture at path: " << filename << std::endl;
        std::cout << "  stbi reason: " << stbi_failure_reason() << std::endl;
    }

    return textureID;

}