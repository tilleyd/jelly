#ifndef _GELI_FRAMEBUFFER_HPP_
#define _GELI_FRAMEBUFFER_HPP_

#include <geli/texture.hpp>

namespace geli
{

/**
 * A framebuffer that can be used as a render target.
 */
class Framebuffer
{

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
     */
    void attach_color(const Texture&, unsigned int index=0);

    /**
     * Attaches a texture as the depth buffer of the framebuffer.
     */
    void attach_depth(const Texture&);

    /**
     * Attaches a texture as both the depth and stencil buffer of the
     * framebuffer.
     */
    void attach_depth_stencil(const Texture&);

    /**
     * Returns the raw OpenGL framebuffer handle.
     */
    unsigned int get_handle() const { return _handle; }

private:

    unsigned int _handle;

};

};

#endif
