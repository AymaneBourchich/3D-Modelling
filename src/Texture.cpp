#include "Texture.hpp"

#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

Texture::Texture(const std::string &filePath)
{
    glGenTextures(1, &textureId);

    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width;
    int height;
    int channelCount;

    stbi_set_flip_vertically_on_load(true);

    unsigned char *data = stbi_load(filePath.c_str(), &width, &height, &channelCount, 0);

    if (data)
    {
        GLenum format = GL_RGB;
        GLenum internalFormat = GL_RGB8;

        if (channelCount == 1)
        {
            format = GL_RED;
            internalFormat = GL_R8;
        }
        else if (channelCount == 3)
        {
            format = GL_RGB;
            internalFormat = GL_RGB8;
        }
        else if (channelCount == 4)
        {
            format = GL_RGBA;
            internalFormat = GL_RGBA8;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Failed to load texture\n";
    }

    stbi_image_free(data);
}

Texture::~Texture()
{
    glDeleteTextures(1, &textureId);
}

void Texture::bind(int slot) const
{
    switch (slot)
    {
        case 0:
        glActiveTexture(GL_TEXTURE0);
        break;

        case 1:
        glActiveTexture(GL_TEXTURE1);
        break;

        case 2:
        glActiveTexture(GL_TEXTURE2);
        break;
    }
    glBindTexture(GL_TEXTURE_2D, textureId);
}