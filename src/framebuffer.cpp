#include <geli/framebuffer.hpp>

#include <stdexcept>

using namespace geli;

Framebuffer::Framebuffer() :
    _handle(0)
{
    glGenFramebuffers(1, &_handle);
}

Framebuffer::~Framebuffer()
{
    glDeleteFramebuffers(1, &_handle);
}

void Framebuffer::attach_color(const Texture& tex, unsigned int i)
{
    glBindFramebuffer(GL_FRAMEBUFFER, _handle);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, tex.get_handle(), 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::attach_depth(const Texture& tex)
{
    glBindFramebuffer(GL_FRAMEBUFFER, _handle);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, tex.get_handle(), 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::attach_depth_stencil(const Texture& tex)
{
    glBindFramebuffer(GL_FRAMEBUFFER, _handle);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, tex.get_handle(), 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
