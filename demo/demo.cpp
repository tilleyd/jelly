#include "demo.hpp"

#include <cmath>

#include <geli/math.hpp>
#include <geli/mesh.hpp>
#include <geli/shader.hpp>

void Demo::create(geli::Window& w)
{
    _counter = 0;

    _camera.attach_to(w);
    geli::Shader::default_shader()->set_uniform("u_P", geli::Mat4f::perspective(DEG_TO_RAD(90.0f), 1280.0f/720.0f, 0.1f, 100.0f));
}

void Demo::draw(geli::Window& w, double p)
{
    w.clear(geli::Vec3f(0.1f));

    // set the view matrix to the camera
    geli::Shader::default_shader()->set_uniform("u_V", _camera.get_view_matrix());

    // draw a moving cube
    double sn = sin(_counter * M_PI / 180.0);
    double cs = cos(_counter * M_PI / 180.0);
    geli::Shader::default_shader()->set_uniform("u_Color", geli::Vec3f(0.0f, (sn + 1.0f) * 0.5f, (cs + 1.0f) * 0.5f));
    geli::Shader::default_shader()->set_uniform("u_M", geli::Mat4f::translation(geli::Vec3f(sn, cs, 0.0f)));
    geli::Mesh::cube_mesh()->render();

    _counter = (_counter + 1) % 360;
}

void Demo::on_key(geli::Window&, int key, int, int act, int)
{
}

void Demo::on_mouse_move(geli::Window&, const geli::Vec2d& p, const geli::Vec2d& r)
{
}
