#ifndef _JELLY_CONTEXT_HPP_
#define _JELLY_CONTEXT_HPP_

#include <map>

#include <jelly/gl/framebuffer.hpp>
#include <jelly/gl/mesh.hpp>
#include <jelly/gl/shader.hpp>

namespace jelly {

class Window;

class Context {

public:

    Context() = delete;
    Context(const Context&) = delete;
    Context& operator=(const Context&) = delete;

    ~Context();

    /**
     * Activates the given shader.
     *
     * All rendered meshes will be shaded using the given shader until another
     * shader is applied.
     */
    void activate_shader(Shader&);

    /**
     * Renders the given mesh using the last applied shader.
     */
    void render_mesh(const Mesh&);

    /**
     * Binds a texture to one of the 16 available texture slots.
     *
     * \warning Certain texture operations such as creating a new texture or
     * generating mipmaps may replace the last bound texture.
     */
    void bind_texture(const Texture&, unsigned int index = 0);

    /**
     * Clears the buffer to the given colour.
     */
    void clear(const Vec3& color);

    /**
     * Uses the given framebuffer as the render target for subsequent rendering.
     *
     * \warning Certain framebuffer operations such as creating a new
     * framebuffer or attaching textures will replace the currently bound
     * framebuffer.
     *
     * \throw std::runtime_error if the framebuffer does not have the necessary
     * attachments or if the format of an attachment is incorrect.
     */
    void set_framebuffer(const Framebuffer&);

    /**
     * Reverts to the default framebuffer (i.e. the window viewport) as the
     * render target for subsequent rendering.
     */
    void reset_framebuffer();

    /**
     * Returns the window that owns this context.
     */
    Window& get_window() { return *_owner; }

private:

    friend class Window;

    Context(Window* owner);

    /**
     * Sets the rendering viewport to the given width and height.
     */
    void _set_viewport(int width, int height);

    Window* _owner;

    Shader* _activeShader;
    std::map<const Texture*, unsigned int> _boundTextures;
    int _vpWidth, _vpHeight;

};

}

#endif
