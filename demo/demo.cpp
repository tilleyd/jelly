#include "demo.hpp"

#include <cmath>
#include <iostream>

#include <geli/math.hpp>
#include <geli/mesh.hpp>
#include <geli/shader.hpp>

using namespace geli;

#define POINT_0_COLOR Vec3f(1.0f, 1.0f, 0.9f)

void Demo::create(Window& w)
{
    _counter = 0;


    // create the geometry meshes
    _cubeMesh = Mesh::create_cube_mesh(0.5f);
    _sphereMesh = Mesh::create_sphere_mesh(16, 16, 0.5f);

    // set up textures
    _emptyTexture = std::make_shared<Texture>(Vec3f(0.0f));
    _woodTexture = std::make_shared<Texture>("res/wood.png");
    _emptyTexture->bind(0);
    _woodTexture->bind(1);
    // bind all samplers to the empty texture for default zero samples
    Shader::default_shader()->set_uniform("u_TexDiffuse", 0);
    Shader::default_shader()->set_uniform("u_TexSpecular", 0);
    Shader::default_shader()->set_uniform("u_TexEmissive", 0);
    Shader::default_shader()->set_uniform("u_TexShininess", 0);

    // set up the camera
    _camera.attach_to(w);
    _projMatrix = Mat4f::perspective(DEG_TO_RAD(75.0f), 1280.0f/720.0f, 0.1f, 100.0f);

    // set up lighting and background
    w.set_clear_color(Vec3f(0.1f));
    Shader::default_shader()->set_uniform("u_AmbientLight", Vec3f(0.2f));
    Shader::default_shader()->set_uniform("u_DirectionalLight.direction", Vec3f(1.0f, -0.8f, 0.5f));
    Shader::default_shader()->set_uniform("u_DirectionalLight.color", Vec3f(1.0f, 1.0f, 1.0f));
    Shader::default_shader()->set_uniform("u_PointLights[0].color", POINT_0_COLOR);
}

void Demo::draw(Window& w, double p)
{
    w.clear();

    // set the view matrix to the camera
    Shader::default_shader()->set_uniform("u_ViewProjMatrix", _projMatrix * _camera.get_view_matrix());
    Shader::default_shader()->set_uniform("u_CameraPosition", _camera.get_position());


    // draw a flat rectangle
    Mat4f modelMatrix = Mat4f::translation(Vec3f(0.0f, -1.05f, 0.0f)) * Mat4f::scale(Vec3f(2.0f, 0.1f, 2.0f));
    Shader::default_shader()->set_uniform("u_ModelMatrix", modelMatrix);
    Shader::default_shader()->set_uniform("u_NormalMatrix", normal_matrix(modelMatrix));
    Shader::default_shader()->set_uniform("u_TexDiffuse", 0);
    Shader::default_shader()->set_uniform("u_Diffuse", Vec3f(0.75f, 0.35f, 0.35f));
    Shader::default_shader()->set_uniform("u_Emissive", Vec3f(0.0f));
    _cubeMesh->render();

    // draw a floating sphere
    double x = sin(DEG_TO_RAD(_counter * 2.0));
    double y = sin(DEG_TO_RAD(_counter));
    double z = cos(DEG_TO_RAD(_counter * 2.0));
    modelMatrix = Mat4f::translation(Vec3f(x, y + 0.5f, z));
    Shader::default_shader()->set_uniform("u_ModelMatrix", modelMatrix);
    Shader::default_shader()->set_uniform("u_NormalMatrix", normal_matrix(modelMatrix));
    Shader::default_shader()->set_uniform("u_TexDiffuse", 1);
    Shader::default_shader()->set_uniform("u_Diffuse", Vec3f(0.0f));
    Shader::default_shader()->set_uniform("u_Emissive", Vec3f(0.0f));
    _sphereMesh->render();

    // draw a circling light sphere
    x = sin(DEG_TO_RAD(_counter * 0.25)) * 2.0;
    z = cos(DEG_TO_RAD(_counter * 0.25)) * 2.0;
    modelMatrix = Mat4f::translation(Vec3f(x, 0.5f, z)) * Mat4f::scale(Vec3f(0.25f));
    Shader::default_shader()->set_uniform("u_ModelMatrix", modelMatrix);
    Shader::default_shader()->set_uniform("u_NormalMatrix", normal_matrix(modelMatrix));
    Shader::default_shader()->set_uniform("u_TexDiffuse", 0);
    Shader::default_shader()->set_uniform("u_Diffuse", Vec3f(0.0f));
    Shader::default_shader()->set_uniform("u_Emissive", POINT_0_COLOR);
    _sphereMesh->render();

    // put the point light on the above light sphere
    Shader::default_shader()->set_uniform("u_PointLights[0].position", Vec3f(x, 0.5f, z));

    ++_counter;
}

void Demo::on_key(Window&, int key, int, int act, int)
{
}

void Demo::on_mouse_move(Window&, const Vec2d& p, const Vec2d& r)
{
}
