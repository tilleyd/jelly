#include <geli/framebuffer.hpp>

#include <stdexcept>

namespace geli {

Framebuffer::Framebuffer() :
    _handle(0),
    _width(-1),
    _height(-1)
{
    glGenFramebuffers(1, &_handle);
}


Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &_handle);
}


void Framebuffer::attach_color(const Texture& tex, unsigned int i) {
    if (_width == -1) {
        _width = tex.get_width();
        _height = tex.get_height();
    } else if (tex.get_width() != _width || tex.get_height() != _height) {
        throw std::runtime_error("Attempt to attach color buffer with incorrect size");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, _handle);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, tex.get_gl_handle(), 0);
    _usedColorBuffers.emplace_back(GL_COLOR_ATTACHMENT0 + i);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void Framebuffer::attach_depth(const Texture& tex) {
    if (_width == -1) {
        _width = tex.get_width();
        _height = tex.get_height();
    } else if (tex.get_width() != _width || tex.get_height() != _height) {
        throw std::runtime_error("Attempt to attach depth buffer with incorrect size");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, _handle);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, tex.get_gl_handle(), 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void Framebuffer::attach_depth_stencil(const Texture& tex) {
    if (_width == -1) {
        _width = tex.get_width();
        _height = tex.get_height();
    } else if (tex.get_width() != _width || tex.get_height() != _height) {
        throw std::runtime_error("Attempt to attach depth+stencil buffer with incorrect size");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, _handle);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, tex.get_gl_handle(), 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void Framebuffer::_bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, _handle);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
        glDrawBuffers(_usedColorBuffers.size(), _usedColorBuffers.data());
    } else {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        throw std::runtime_error("Attempt to use incorrectly formed framebuffer");
    }
}


}
