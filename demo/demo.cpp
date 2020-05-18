#include "demo.h"

#include <cmath>

#include <geli/math.hpp>
#include <geli/mesh.hpp>
#include <geli/shader.hpp>

void Demo::create(geli::Window&)
{
    _counter = 0;
    geli::Shader::default_shader()->set_uniform("u_P", geli::Mat4f::perspective(90.0f, 1280.0f/720.0f, 0.1f, 100.0f));
    geli::Shader::default_shader()->set_uniform("u_V", geli::Mat4f::translation(geli::Vec3f(0.0f, 0.0f, -2.0f)));
}

void Demo::draw(geli::Window&, double p)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.15f, 0.15f, 0.15f, 1.f);
    geli::Mesh::cube_mesh()->render();

    double sn = sin(_counter * M_PI / 180.0);
    double cs = cos(_counter * M_PI / 180.0);
    geli::Shader::default_shader()->set_uniform("u_Color", geli::Vec3f(0.0f, (sn + 1.0f) * 0.5f, (cs + 1.0f) * 0.5f));
    geli::Shader::default_shader()->set_uniform("u_M", geli::Mat4f::translation(geli::Vec3f(cs, sn, 0.0f)));

    _counter = (_counter + 1) % 360;
}
