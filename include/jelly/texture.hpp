#ifndef _JELLY_TEXTURE_HPP_
#define _JELLY_TEXTURE_HPP_

#include <string>

#include <GL/glew.h>

#include <jelly/math/vec2.hpp>
#include <jelly/math/vec3.hpp>

namespace jelly {

/**
 * A texture that can be applied to a shader or used as a render target when
 * using framebuffers.
 */
class Texture {

public:

    /**
     * Texture types.
     */
    enum class Type {
        TEXTURE_2D,
        TEXTURE_CUBE
    };

    /**
     * Texture pixel formats.
     */
    enum class Format {
        GRAY = GL_LUMINANCE,
        GRAYA = GL_LUMINANCE_ALPHA,
        RGB = GL_RGB,
        RGB16F = GL_RGB16F,
        RGB32F = GL_RGB32F,
        SRGB = GL_SRGB,
        RGBA = GL_RGBA,
        RGBA16F = GL_RGBA16F,
        RGBA32F = GL_RGBA32F,
        SRGBA = GL_SRGB_ALPHA,

        DEPTH = GL_DEPTH_COMPONENT,
        DEPTH_STENCIL = GL_DEPTH_STENCIL
    };

    /**
     * Texture filtering types.
     */
    enum class Filter {
        NEAREST = GL_NEAREST,
        LINEAR = GL_LINEAR
    };

    /**
     * Creates an empty texture.
     *
     * \param width
     *     The pixel width of the texture.
     * \param height
     *     The pixel height of the texture.
     * \param format
     *     The pixel format of the texture.
     * \param filter
     *     The min/mag texture filtering to use.
     * \param type
     *     The type of the texture.
     */
    Texture(
        int width,
        int height,
        Format format = Format::RGB,
        Filter filter = Filter::LINEAR,
        Type type = Type::TEXTURE_2D
    );

    /**
     * Creates a 2D texture from a given image file.
     *
     * \param path
     *     The filename of a valid image.
     * \param srgb
     *     If true, the SRGB/SRGBA format will be chosen instead of RGB/RGBA.
     * \param filter
     *     The min/mag texture filtering to use.
     *
     * \throw std::runtime_error if the image could not be loaded.
     */
    Texture(std::string path, Filter filter = Filter::LINEAR, bool srgb = false);

    /**
     * Creates a cubemap texture from 6 individual image files.
     *
     * \param fns
     *     The filenames of 6 valid images. The following order is assumed:
     *         0 - positive x
     *         1 - negative x
     *         2 - positive y
     *         3 - negative y
     *         4 - positive z
     *         5 - negative z
     * \param srgb
     *     If true, the SRGB/SRGBA format will be chosen instead of RGB/RGBA.
     * \param filter
     *     The min/mag texture filtering to use.
     *
     * \throw std::runtime_error if the images could not be loaded or if the images
     * differ in format or size.
     */
    Texture(std::string fns[6], Filter filter = Filter::LINEAR, bool srgb = false);

    /**
     * Creates a 1x1 2D texture that can be used to sample a constant value.
     *
     * \param v
     *     The RGB value of the single pixel.
     */
    Texture(const Vec3& v);

    /**
     * Clears memory used by the texture.
     */
    ~Texture();

    /**
     * Generates mipmaps for this texture.
     */
    void generate_mipmaps();

    /**
     * Returns the format of the texture.
     */
    Format get_format() const { return _format; }

    /**
     * Returns the width of the texture in pixels.
     */
    int get_width() const { return _width; }

    /**
     * Returns the height of the texture in pixels.
     */
    int get_height() const { return _height; }

    /**
     * Returns the size of the texture in pixels.
     */
    Vec2 get_size() const { return Vec2(_width, _height); }

    /**
     * Returns the raw OpenGL texture handle.
     */
    unsigned int get_gl_handle() const { return _handle; }

private:

    friend class Context;

    void _bind(unsigned int index) const;

    unsigned int _handle;
    Type         _type;
    Format       _format;
    int          _width, _height;

};

};

#endif
