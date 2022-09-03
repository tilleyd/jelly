#include <jelly/texture.hpp>

#include <stdexcept>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace jelly {


Texture::Texture(int width, int height, Format format, Filter filter, Type type) :
    _handle(0),
    _type(type),
    _format(format),
    _width(width),
    _height(height)
{
    glGenTextures(1, &_handle);

    unsigned int bindTarget = (type == Type::TEXTURE_2D ? GL_TEXTURE_2D : GL_TEXTURE_CUBE_MAP);
    glBindTexture(bindTarget, _handle);
    glTexParameteri(bindTarget, GL_TEXTURE_MIN_FILTER, (unsigned int)filter);
    glTexParameteri(bindTarget, GL_TEXTURE_MAG_FILTER, (unsigned int)filter);

    // Some formats need specific internal/external formats and pixel types
    unsigned int intFormat = (unsigned int)format;
    unsigned int extFormat = intFormat;
    unsigned int pixelType = GL_UNSIGNED_BYTE;
    switch (format) {
        case Format::SRGB:
            extFormat = GL_RGB;
            break;
        case Format::RGB16F:
            extFormat = GL_RGB;
            pixelType = GL_FLOAT;
            break;
        case Format::RGB32F:
            extFormat = GL_RGB;
            pixelType = GL_FLOAT;
            break;
        case Format::SRGBA:
            extFormat = GL_RGBA;
            break;
        case Format::RGBA16F:
            extFormat = GL_RGBA;
            pixelType = GL_FLOAT;
            break;
        case Format::RGBA32F:
            extFormat = GL_RGBA;
            pixelType = GL_FLOAT;
            break;
        case Format::DEPTH:
            intFormat = GL_DEPTH_COMPONENT24;
            break;
        case Format::DEPTH_STENCIL:
            intFormat = GL_DEPTH24_STENCIL8;
            pixelType = GL_UNSIGNED_INT_24_8;
            break;
    }

    if (type == Type::TEXTURE_CUBE) {
        // Set wrapping type
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        // Create texture buffers for each face
        for (unsigned int i = 0; i < 6; ++i) {
            glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0,
                intFormat,
                width,
                height,
                0,
                extFormat,
                pixelType,
                nullptr
            );
        }
    } else {
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            intFormat,
            width,
            height,
            0,
            extFormat,
            pixelType,
            nullptr
        );
    }
}


Texture::Texture(std::string path, Filter filter, bool srgb) :
    _handle(0),
    _type(Type::TEXTURE_2D)
{
    int width, height, channels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (data) {
        glGenTextures(1, &_handle);
        glBindTexture(GL_TEXTURE_2D, _handle);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (unsigned int)filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (unsigned int)filter);

        // Choose the data format
        Format format, extFormat;
        switch (channels) {
            case 1:
                format = Format::GRAY;
                extFormat = Format::GRAY;
                break;
            case 3:
                format = srgb ? Format::SRGB : Format::RGB;
                extFormat = Format::RGB;
                break;
            case 4:
                format = srgb ? Format::SRGBA : Format::RGBA;
                extFormat = Format::RGBA;
                break;
            default:
                throw std::runtime_error("Unknown image format");
                break;
        }

        _format = format;
        _width = width;
        _height = height;
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            (unsigned int)format,
            width,
            height,
            0,
            (unsigned int)extFormat,
            GL_UNSIGNED_BYTE,
            data
        );

        stbi_image_free(data);
    } else {
        throw std::runtime_error("Could not load texture \'" + path + "\'");
    }
}


Texture::Texture(std::string fns[6], Filter filter, bool srgb) :
    _handle(0),
    _type(Type::TEXTURE_CUBE)
{
    int width, height, channels;
    unsigned char* data[6] = {};

    data[0] = stbi_load(fns[0].c_str(), &width, &height, &channels, 0);
    if (!data[0]) {
        throw std::runtime_error("could not load texture \'" + fns[0] + "\'");
    }

    // Check that all images are similar in format
    for (unsigned int i = 1; i < 6; ++i) {
        int w, h, c;
        data[i] = stbi_load(fns[i].c_str(), &w, &h, &c, 0);
        if (!data[i] || w != width || h != height || c != channels) {
            // Delete all images including this one
            for (unsigned int j = 0; j <= i; ++j) {
                stbi_image_free(data[j]);
            }
            if (data[i]) {
                throw std::runtime_error("Cube textures must have similar formats");
            } else {
                throw std::runtime_error("Could not load texture \'" + fns[i] + "\'");
            }
        }
    }

    glGenTextures(1, &_handle);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _handle);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, (unsigned int)filter);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, (unsigned int)filter);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // Choose the data format
    Format format, extFormat;
    switch (channels) {
        case 1: format = Format::GRAY; extFormat = Format::GRAY; break;
        case 3: format = srgb ? Format::SRGB : Format::RGB; extFormat = Format::RGB; break;
        case 4: format = srgb ? Format::SRGBA : Format::RGBA; extFormat = Format::RGBA; break;
        default: throw std::runtime_error("unknown image format"); break;
    }

    _width = width;
    _height = height;
    _format = format;
    // create the texture buffers
    for (unsigned int i = 0; i < 6; ++i) {
        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
            0,
            (unsigned int)format,
            width,
            height,
            0,
            (unsigned int)extFormat,
            GL_UNSIGNED_BYTE,
            data[i]
        );
        stbi_image_free(data[i]);
    }
}


Texture::Texture(const Vec3& v) :
    _handle(0),
    _type(Type::TEXTURE_2D),
    _format(Format::RGB),
    _width(1),
    _height(1)
{
    glGenTextures(1, &_handle);
    glBindTexture(GL_TEXTURE_2D, _handle);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_FLOAT, v.data());
}


Texture::~Texture() {
    glDeleteTextures(1, &_handle);
}


void Texture::generate_mipmaps() {
    glBindTexture(GL_TEXTURE_2D, _handle);
    glGenerateMipmap(GL_TEXTURE_2D);
}


void Texture::_bind(unsigned int i) const {
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, _handle);
}


}
