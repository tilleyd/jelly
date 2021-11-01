#include <geli/context.hpp>

#include <GL/glew.h>

#include <geli/window.hpp>

namespace geli {


Context::Context(Window* owner) :
    _owner(owner),
    _activeShader(nullptr)
{}


Context::~Context() {}


void Context::activate_shader(Shader& shader) {
    Shader* ptr = &shader;

    if (_activeShader != ptr) {
        if (_activeShader != nullptr) {
            _activeShader->_deactivate();
        }
        _activeShader = ptr;
        ptr->_activate(this);
    }
}


void Context::render_mesh(const Mesh& mesh) {
    mesh._render();
}


void Context::clear(const Vec3& color) {
    glClearColor(color.x(), color.y(), color.z(), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}


/* void Context::set_framebuffer(const Framebuffer& fb, const std::vector<unsigned int>* buffers)
{
    glBindFramebuffer(GL_FRAMEBUFFER, fb.get_handle());

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
        // leave the framebuffer bound and set remaining properties
        if (buffers) {
            glDrawBuffers(buffers->size(), buffers->data());
        } else {
            glDrawBuffer(GL_COLOR_ATTACHMENT0);
        }
    } else {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        throw std::runtime_error("attempt to use incorrectly formed framebuffer");
    }
} */


/* void Context::reset_framebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
} */


}
