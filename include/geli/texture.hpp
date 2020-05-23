#ifndef _GELI_TEXTURE_HPP_
#define _GELI_TEXTURE_HPP_

#include <string>

#include <GL/glew.h>

namespace geli
{

/**
 * A 2D texture that can be applied to a shader or used as a render target when
 * using framebuffers.
 */
class Texture
{

/**
 * Texture pixel formats.
 */
enum class Format
{
    GRAY = GL_RED,
    RGB = GL_RGB,
    RGBA = GL_RGBA
};

/**
 * Texture filtering types.
 */
enum class Filter
{
    NEAREST = GL_NEAREST,
    LINEAR = GL_LINEAR
};

public:

/**
 * Creates an empty texture.
 *
 * \param width
 *     The width of the texture.
 * \param height
 *     The height of the texture.
 * \param format
 *     The pixel format of the texture.
 * \param filter
 *     The min/mag texture filtering to use.
 */
Texture(unsigned int width, unsigned int height, Format format = Format::RGB, Filter filter = Filter::LINEAR);

/**
 * Creates a texture from a given image file.
 *
 * \param fn
 *     The filename of a valid image.
 * \param filter
 *     The min/mag texture filtering to use.
 *
 * \throw std::runtime_error if the image could not be loaded.
 */
Texture(std::string fn, Filter filter = Filter::LINEAR);

/**
 * Clears memory used by the texture.
 */
~Texture();

/**
 * Generates mipmaps for this texture.
 */
void generate_mipmaps();

/**
 * Binds a texture to on of the 16 available texture slots. To be used with
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
 * Returns the raw OpenGL texture handle.
 */
unsigned int get_handle() const { return _handle; }

private:

    unsigned int _handle;

};

};

#endif
