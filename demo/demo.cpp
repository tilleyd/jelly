#include "demo.h"

#include <cmath>

#include <geli/mesh.hpp>
#include <geli/shader.hpp>

void Demo::create(geli::Window&)
{
    _counter = 0;
}

void Demo::draw(geli::Window&, double p)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.15f, 0.15f, 0.15f, 1.f);
    geli::Mesh::cube_mesh()->render();

    double f = sin(_counter * M_PI / 180.0) + 1.0 * 0.5;
    geli::Shader::default_shader()->set_uniform("u_Color", geli::Vec3f(f, 1.0f, 1.0f));

    _counter = (_counter + 1) % 360;
}
