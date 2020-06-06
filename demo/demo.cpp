#include "demo.hpp"

#include <cmath>
#include <iostream>

#include <geli/math.hpp>
#include <geli/mesh.hpp>
#include <geli/shader.hpp>

using namespace geli;

#define RED_LIGHT_COLOR Vec3f(2.0f, 0.1f, 0.1f)
#define GREEN_LIGHT_COLOR Vec3f(0.1f, 2.0f, 0.1f)
#define BLUE_LIGHT_COLOR Vec3f(0.1f, 0.1f, 2.0f)

void Demo::create(Window& w, Renderer& r)
{
    _counter = 0;
    int width = w.get_size().x();
    int height = w.get_size().y();

    // set up the camera
    _camera.attach_to(w);
    r.set_projection_matrix(Mat4f::perspective(DEG_TO_RAD(75.0f), width/float(height), 0.1f, 100.0f));

    // create the meshes
    unsigned int cubeMesh = r.add_mesh(Mesh::create_cube_mesh(0.5f));
    unsigned int sphereMesh = r.add_mesh(Mesh::create_sphere_mesh(16, 16, 0.5f));

    // create the materials
    std::shared_ptr<Material> mat = std::make_shared<Material>();
    mat->set_diffuse_texture(std::make_shared<Texture>("res/wood.png", true));
    unsigned int woodMaterial = r.add_material(mat);

    mat = std::make_shared<Material>();
    mat->set_diffuse(Vec3f(0.2f));
    mat->set_specular(Vec3f(1.0f));
    mat->set_shininess(500.0f);
    unsigned int metalMaterial = r.add_material(mat);

    mat = std::make_shared<Material>();
    mat->set_emissive(RED_LIGHT_COLOR);
    unsigned int redLightMaterial = r.add_material(mat);

    mat = std::make_shared<Material>();
    mat->set_emissive(GREEN_LIGHT_COLOR);
    unsigned int greenLightMaterial = r.add_material(mat);

    mat = std::make_shared<Material>();
    mat->set_emissive(BLUE_LIGHT_COLOR);
    unsigned int blueLightMaterial = r.add_material(mat);

    // create the renderables
    _sphere = r.create_renderable();
    _sphere->set_mesh(sphereMesh);
    _sphere->set_material(woodMaterial);

    _platform = r.create_renderable();
    _platform->set_mesh(cubeMesh);
    _platform->set_material(metalMaterial);
    _platform->set_local_transform(Mat4f::translation(Vec3f(0.0f, -1.05f, 0.0f))
                                   * Mat4f::scale(Vec3f(10.0f, 0.1f, 10.0f)));

    _redLight = _sphere->create_child();
    _redLight->set_mesh(sphereMesh);
    _redLight->set_material(redLightMaterial);
    _redLight->attach_light(Light::Type::POINT).set_color(RED_LIGHT_COLOR);

    _greenLight = _sphere->create_child();
    _greenLight->set_mesh(sphereMesh);
    _greenLight->set_material(greenLightMaterial);
    _greenLight->attach_light(Light::Type::POINT).set_color(GREEN_LIGHT_COLOR);

    _blueLight = _sphere->create_child();
    _blueLight->set_mesh(sphereMesh);
    _blueLight->set_material(blueLightMaterial);
    _blueLight->attach_light(Light::Type::POINT).set_color(BLUE_LIGHT_COLOR);

    // set the skybox and environment lighting
    std::string skyboxTexs[6] = {
        "res/side.png",
        "res/side.png",
        "res/top.png",
        "res/bottom.png",
        "res/side.png",
        "res/side.png"
    };
    r.set_skybox(std::make_shared<Texture>(skyboxTexs, true));
    r.set_ambient_light(Vec3f(0.5f));
}

void Demo::draw(Window& w, Renderer& r, double p)
{
    // update to the camera position
    r.set_view_matrix(_camera.get_view_matrix());
    r.set_camera_position(_camera.get_position());

    // update the sphere
    double x = sin(DEG_TO_RAD(_counter * 2.0));
    double y = sin(DEG_TO_RAD(_counter));
    double z = cos(DEG_TO_RAD(_counter * 2.0));
    _sphere->set_local_transform(Mat4f::translation(Vec3f(x, y + 0.5f, z)));

    // update the lights
    x = sin(DEG_TO_RAD(_counter * 0.25)) * 2.0;
    z = cos(DEG_TO_RAD(_counter * 0.25)) * 2.0;
    _redLight->set_local_transform(Mat4f::translation(Vec3f(x, 0.5f, z)) * Mat4f::scale(Vec3f(0.25f)));

    x = sin(DEG_TO_RAD(_counter * 0.25 + 120.0)) * 2.0;
    z = cos(DEG_TO_RAD(_counter * 0.25 + 120.0)) * 2.0;
    _greenLight->set_local_transform(Mat4f::translation(Vec3f(x, 0.5f, z)) * Mat4f::scale(Vec3f(0.25f)));

    x = sin(DEG_TO_RAD(_counter * 0.25 + 240.0)) * 2.0;
    z = cos(DEG_TO_RAD(_counter * 0.25 + 240.0)) * 2.0;
    _blueLight->set_local_transform(Mat4f::translation(Vec3f(x, 0.5f, z)) * Mat4f::scale(Vec3f(0.25f)));

    r.render();

    ++_counter;
}

void Demo::on_key(Window&, int key, int, int act, int)
{
}

void Demo::on_mouse_move(Window&, const Vec2d& p, const Vec2d& r)
{
}
