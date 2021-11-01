#ifndef _DEMO_H_
#define _DEMO_H_

#include <memory>

#include <geli/shader.hpp>
#include <geli/texture.hpp>
#include <geli/window.hpp>
#include <geli/mesh.hpp>

class Demo
{

public:

    Demo();

    ~Demo();

    void create(geli::Window&, geli::Context&);

    void draw(geli::Window&, geli::Context&, double p);

    void on_key(geli::Window&, int, int, int, int);

    void on_mouse_move(geli::Window&, const geli::Vec2&, const geli::Vec2&);

private:

    std::string load_file(const std::string& path) const;

    geli::Shader* _shader;
    geli::Mesh*   _square;

};

#endif
