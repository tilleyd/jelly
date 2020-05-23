#include <geli/texture.hpp>

#include <stdexcept>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace geli;

Texture::Texture(unsigned int w, unsigned int h, Format format, Filter filter) :
    _handle(0)
{
    glGenTextures(1, &_handle);
    glBindTexture(GL_TEXTURE_2D, _handle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (unsigned int)filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (unsigned int)filter);

    glTexImage2D(GL_TEXTURE_2D, 0, (unsigned int)format, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
}

Texture::Texture(std::string fn, Filter filter) :
    _handle(0)
{
    int w, h, channels;
    unsigned char* data = stbi_load(fn.c_str(), &w, &h, &channels, 0);
    if (data) {
        glGenTextures(1, &_handle);
        glBindTexture(GL_TEXTURE_2D, _handle);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (unsigned int)filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (unsigned int)filter);

        // choose the data format
        Format format;
        switch (channels) {
            case 1: format = Format::GRAY; break;
            case 3: format = Format::RGB; break;
            case 4: format = Format::RGBA; break;
            default: throw std::runtime_error("unknown image format"); break;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, (unsigned int)format, w, h, 0, (unsigned int)format, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    } else {
        throw std::runtime_error("could not load texture");
    }
}

Texture::~Texture()
{
    glDeleteTextures(1, &_handle);
}

void Texture::generate_mipmaps()
{
    glBindTexture(GL_TEXTURE_2D, _handle);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::bind(unsigned int i)
{
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, _handle);
}
