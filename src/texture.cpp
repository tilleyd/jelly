#include <geli/texture.hpp>

#include <stdexcept>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace geli;

Texture::Texture(const Vec2i& size, Format format, Filter filter) :
    _handle(0),
    _format(format),
    _size(size)
{
    glGenTextures(1, &_handle);
    glBindTexture(GL_TEXTURE_2D, _handle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (unsigned int)filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (unsigned int)filter);

    // some formats need specific internal/external formats and types
    unsigned int intFormat = (unsigned int)format;
    unsigned int extFormat = intFormat;
    unsigned int type = GL_UNSIGNED_BYTE;
    switch (format) {
        case Format::RGB16F:
            extFormat = GL_RGB;
            type = GL_FLOAT;
            break;
        case Format::RGB32F:
            extFormat = GL_RGB;
            type = GL_FLOAT;
            break;
        case Format::RGBA16F:
            extFormat = GL_RGBA;
            type = GL_FLOAT;
            break;
        case Format::RGBA32F:
            extFormat = GL_RGBA;
            type = GL_FLOAT;
            break;
        case Format::DEPTH:
            intFormat = GL_DEPTH_COMPONENT24;
            break;
        case Format::DEPTH_STENCIL:
            intFormat = GL_DEPTH24_STENCIL8;
            type = GL_UNSIGNED_INT_24_8;
            break;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, intFormat, size.x(), size.y(), 0, extFormat, type, NULL);
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

        _format = format;
        _size = Vec2i(w, h);
        glTexImage2D(GL_TEXTURE_2D, 0, (unsigned int)format, w, h, 0, (unsigned int)format, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    } else {
        throw std::runtime_error("could not load texture");
    }
}

Texture::Texture(const Vec3f& v) :
    _handle(0),
    _format(Format::RGB),
    _size(Vec2i(1, 1))
{
    glGenTextures(1, &_handle);
    glBindTexture(GL_TEXTURE_2D, _handle);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_FLOAT, v.data());
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
