#ifndef _GELI_CONTEXT_HPP_
#define _GELI_CONTEXT_HPP_

#include <geli/mesh.hpp>
#include <geli/shader.hpp>

namespace geli {

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
     * Clears the buffer to the given colour.
     */
    void clear(const Vec3& color);

    /**
     * Uses the given framebuffer as the render target for subsequent rendering.
     *
     * \param buffers
     *     A vector of color buffer indices to use as active targets. Only
     *     used if multiple textures were attached to the buffer as color
     *     attachments. If null, only the first color buffer will be used.
     *
     * \warning Certain framebuffer operations such as creating a new
     * framebuffer or attaching textures will replace the currently bound
     * framebuffer.
     *
     * \throw std::runtime_error if the framebuffer does not have the necessary
     * attachments or if the format of an attachment is incorrect.
     */
    // void set_framebuffer(const Framebuffer&, const std::vector<unsigned int>* buffers = nullptr);

    /**
     * Reverts to the default framebuffer (i.e. the window viewport) as the
     * render target for subsequent rendering.
     */
    // void reset_framebuffer();

    /**
     * Returns the window that owns this context.
     */
    Window& get_window() { return *_owner; }

private:

    friend class Window;

    Context(Window* owner);

    Window* _owner;
    Shader* _activeShader;

};

}

#endif
