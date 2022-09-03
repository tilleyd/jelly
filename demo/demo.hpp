#ifndef _DEMO_H_
#define _DEMO_H_

#include <memory>

#include <jelly/framebuffer.hpp>
#include <jelly/mesh.hpp>
#include <jelly/shader.hpp>
#include <jelly/texture.hpp>
#include <jelly/window.hpp>

class Demo
{

public:

    Demo();

    ~Demo();

    void create(jelly::Window&, jelly::Context&);

    void draw(jelly::Window&, jelly::Context&, double p);

    void on_key(jelly::Window&, int, int, int, int);

    void on_mouse_move(jelly::Window&, const jelly::Vec2&, const jelly::Vec2&);

private:

    std::string load_file(const std::string& path) const;

    jelly::Shader*  _shader;
    jelly::Mesh*    _square;
    jelly::Texture* _wood;

    jelly::Texture* _colorBuffer;
    jelly::Framebuffer* _framebuffer;

};

#endif
