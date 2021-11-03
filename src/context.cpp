#include <geli/context.hpp>

#include <GL/glew.h>

#include <geli/window.hpp>

namespace geli {


Context::Context(Window* owner) :
    _owner(owner),
    _activeShader(nullptr)
{
    Vec2 windowSize = owner->get_size();
    _vpWidth = windowSize.x();
    _vpHeight = windowSize.y();
}


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


void Context::bind_texture(const Texture& tex, unsigned int index) {
    // TODO avoid binding if texture is already bound
    tex._bind(index);
}


void Context::clear(const Vec3& color) {
    glClearColor(color.x(), color.y(), color.z(), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}


void Context::set_framebuffer(const Framebuffer& fb) {
    fb._bind();

    _set_viewport(fb.get_width(), fb.get_height());
}


void Context::reset_framebuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);

    _set_viewport(_owner->get_width(), _owner->get_height());
}

void Context::_set_viewport(int width, int height) {
    if (width != _vpWidth || height != _vpHeight) {
        glViewport(0, 0, width, height);
        _vpWidth = width;
        _vpHeight = height;
    }
}


}
