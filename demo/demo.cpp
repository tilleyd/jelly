#include "demo.hpp"

#include <cmath>

#include <geli/math.hpp>
#include <geli/mesh.hpp>
#include <geli/shader.hpp>

using namespace geli;

void Demo::create(Window& w)
{
    _counter = 0;

    _camera.attach_to(w);
    Shader::default_shader()->set_uniform("u_P", Mat4f::perspective(DEG_TO_RAD(90.0f), 1280.0f/720.0f, 0.1f, 100.0f));
}

void Demo::draw(Window& w, double p)
{
    w.clear(Vec3f(0.1f));

    // set the view matrix to the camera
    Shader::default_shader()->set_uniform("u_V", _camera.get_view_matrix());

    // draw a flat rectangle
    Shader::default_shader()->set_uniform("u_Color", Vec3f(0.95f, 0.2f, 0.2f));
    Shader::default_shader()->set_uniform("u_M", Mat4f::translation(Vec3f(0.0f, -1.05f, 0.0f)) * Mat4f::scale(Vec3f(2.0f, 0.1f, 2.0f)));
    Mesh::cube_mesh()->render();

    // draw a floating cube
    double x = sin(DEG_TO_RAD(_counter * 2.0));
    double y = sin(DEG_TO_RAD(_counter));
    double z = cos(DEG_TO_RAD(_counter * 2.0));
    Shader::default_shader()->set_uniform("u_Color", Vec3f(0.8f, 0.8f, 0.8f));
    Shader::default_shader()->set_uniform("u_M", Mat4f::translation(Vec3f(x, y + 0.5f, z)));
    Mesh::cube_mesh()->render();

    _counter = (_counter + 1) % 360;
}

void Demo::on_key(Window&, int key, int, int act, int)
{
}

void Demo::on_mouse_move(Window&, const Vec2d& p, const Vec2d& r)
{
}
