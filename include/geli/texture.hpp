#ifndef _GELI_TEXTURE_HPP_
#define _GELI_TEXTURE_HPP_

#include <string>

#include <GL/glew.h>

#include <geli/math.hpp>

namespace geli
{

/**
 * A texture that can be applied to a shader or used as a render target when
 * using framebuffers. Supports various formats and types, including regular 2D
 * and cubemap textures.
 */
class Texture
{

public:

/**
 * Texture types.
 */
enum class Type
{
    TEXTURE_2D,
    TEXTURE_CUBE
};

/**
 * Texture pixel formats.
 */
enum class Format
{
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
enum class Filter
{
    NEAREST = GL_NEAREST,
    LINEAR = GL_LINEAR
};

/**
 * Creates an empty texture.
 *
 * \param size
 *     The width and height of the texture. If the type is a cube, this is the
 *     size of each individual face.
 * \param format
 *     The pixel format of the texture.
 * \param filter
 *     The min/mag texture filtering to use.
 * \param type
 *     The type of the texture.
 */
Texture(const Vec2i& size, Format format = Format::RGB, Filter filter = Filter::LINEAR, Type type = Type::TEXTURE_2D);

/**
 * Creates a 2D texture from a given image file.
 *
 * \param fn
 *     The filename of a valid image.
 * \param isSrgb
 *     If true, the SRGB/SRGBA format will be chosen instead of RGB/RGBA.
 * \param filter
 *     The min/mag texture filtering to use.
 *
 * \throw std::runtime_error if the image could not be loaded.
 */
Texture(std::string fn, bool isSrgb = false, Filter filter = Filter::LINEAR);

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
 * \param isSrgb
 *     If true, the SRGB/SRGBA format will be chosen instead of RGB/RGBA.
 * \param filter
 *     The min/mag texture filtering to use.
 *
 * \throw std::runtime_error if the images could not be loaded or if the images
 * differ in format or size.
 */
Texture(std::string fns[6], bool isSrgb = false, Filter filter = Filter::LINEAR);

/**
 * Creates a single-pixel 2D texture that can be used to sample a constant value
 * throughout.
 *
 * \param v
 *     The value of the single pixel.
 */
Texture(const Vec3f& v);

/**
 * Clears memory used by the texture.
 */
~Texture();

/**
 * Generates mipmaps for this texture.
 */
void generate_mipmaps();

/**
 * Binds a texture to one of the 16 available texture slots. To be used with
 * a sampler, the sampler2D uniform must also be set to this index.
 *
 * \param index
 *     The texture index, ranging from 0 to 15, inclusive.
 *
 * \warn Certain texture operations such as creating a new texture or generating
 * mipmaps may replace the last bound texture.
 */
void bind(unsigned int index);

/**
 * Returns the format of the texture.
 */
Format get_format() const { return _format; }

/**
 * Returns the raw OpenGL texture handle.
 */
unsigned int get_handle() const { return _handle; }

/**
 * Returns the size of the texture.
 */
Vec2i get_size() const { return _size; }

private:

    unsigned int _handle;
    Type         _type;
    Format       _format;
    Vec2i        _size;

};

};

#endif
