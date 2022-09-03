#ifndef _JELLY_FRAMEBUFFER_HPP_
#define _JELLY_FRAMEBUFFER_HPP_

#include <vector>

#include <jelly/gl/texture.hpp>

namespace jelly {

/**
 * A framebuffer that can be used as a render target.
 */
class Framebuffer {

public:

    /**
     * Creates a handle that textures can be attached to.
     */
    Framebuffer();

    /**
     * Destroys the framebuffer handle.
     */
    ~Framebuffer();

    /**
     * Attaches a texture as one of the 16 available color attachments of the
     * framebuffer.
     *
     * \param index
     *     The color attachment index, ranging from 0 to 15, inclusive.
     *
     * \throw std::runtime_error if the texture size differs from other attached
     * textures.
     */
    void attach_color(const Texture&, unsigned int index=0);

    /**
     * Attaches a texture as the depth buffer of the framebuffer.
     *
     * \throw std::runtime_error if the texture size differs from other attached
     * textures.
     */
    void attach_depth(const Texture&);

    /**
     * Attaches a texture as both the depth and stencil buffer of the
     * framebuffer.
     *
     * \throw std::runtime_error if the texture size differs from other attached
     * textures.
     */
    void attach_depth_stencil(const Texture&);

    /**
     * Returns the raw OpenGL framebuffer handle.
     */
    unsigned int get_gl_handle() const { return _handle; }

    /**
     * Returns the width of the framebuffer in pixels or -1 if no buffers
     * have been attached yet.
     */
    unsigned int get_width() const { return _width; }

    /**
     * Returns the height of the framebuffer in pixels or -1 if no buffers
     * have been attached yet.
     */
    unsigned int get_height() const { return _height; }

    /**
     * Returns the size of the framebuffer in pixels or (-1, -1) if no buffers
     * have been attached yet.
     */
    Vec2 get_size() const { return Vec2(_width, _height); }

private:

    friend class Context;

    void _bind() const;

    unsigned int _handle;
    std::vector<unsigned int> _usedColorBuffers;
    int _width, _height;

};

}

#endif
