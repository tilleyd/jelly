#include "demo.hpp"

#include <cmath>
#include <iostream>

#include <geli/math.hpp>
#include <geli/mesh.hpp>
#include <geli/shader.hpp>

using namespace geli;

#define POINT_0_COLOR Vec3f(0.1f, 0.1f, 2.0f)
#define POINT_1_COLOR Vec3f(0.1f, 2.0f, 0.1f)
#define POINT_2_COLOR Vec3f(2.0f, 0.1f, 0.1f)

void Demo::create(Window& w)
{
    _counter = 0;
    w.set_clear_color(Vec3f(0.01f));

    // create the shader
    _geomShader = Shader::create_single_pass_shader();
    _skyboxShader = Shader::create_skybox_shader();
    _bloomShader = Shader::create_bloom_shader();
    _postShader = Shader::create_post_shader();

    // create the geometry meshes
    _squareMesh = Mesh::create_square_mesh();
    _cubeMesh = Mesh::create_cube_mesh(1.0f);
    _sphereMesh = Mesh::create_sphere_mesh(16, 16, 0.5f);

    // set up textures
    _emptyTexture = std::make_shared<Texture>(Vec3f(0.0f));
    _woodTexture = std::make_shared<Texture>("res/wood.png", true);
    std::string skyboxTexs[6] = {
        "res/side.png",
        "res/side.png",
        "res/top.png",
        "res/bottom.png",
        "res/side.png",
        "res/side.png"
    };
    _skyboxCube = std::make_shared<Texture>(skyboxTexs, true);

    // set up the framebuffer
    _colorBuffer1 = std::make_shared<Texture>(w.get_size(), Texture::Format::RGB16F);
    _colorBuffer2 = std::make_shared<Texture>(w.get_size(), Texture::Format::RGB16F);
    _colorBuffer3 = std::make_shared<Texture>(w.get_size(), Texture::Format::RGB16F);
    _depthBuffer = std::make_shared<Texture>(w.get_size(), Texture::Format::DEPTH);
    _framebuffer = std::make_shared<Framebuffer>();
    _framebuffer->attach_depth(*_depthBuffer);

    _emptyTexture->bind(0);
    _woodTexture->bind(1);
    _colorBuffer1->bind(2);
    _colorBuffer2->bind(3);
    _colorBuffer3->bind(4);

    // set up the camera
    _camera.attach_to(w);
    _projMatrix = Mat4f::perspective(DEG_TO_RAD(75.0f), 1280.0f/720.0f, 0.1f, 100.0f);

    _geomShader->use();
    // bind all samplers to the empty texture for default zero samples
    _geomShader->set_uniform("u_TexDiffuse", 0);
    _geomShader->set_uniform("u_TexSpecular", 0);
    _geomShader->set_uniform("u_TexEmissive", 0);
    _geomShader->set_uniform("u_TexShininess", 0);
    // set up lighting
    _geomShader->set_uniform("u_AmbientLight", Vec3f(0.5f));
    _geomShader->set_uniform("u_DirectionalLight.direction", Vec3f(1.0f, -0.8f, 0.5f));
    _geomShader->set_uniform("u_DirectionalLight.color", Vec3f(5.0f, 5.0f, 4.9f));
    _geomShader->set_uniform("u_PointLights[0].color", POINT_0_COLOR);
    _geomShader->set_uniform("u_PointLights[1].color", POINT_1_COLOR);
    _geomShader->set_uniform("u_PointLights[2].color", POINT_2_COLOR);

    // bind the color buffer samplers to the corresponding buffers
    _postShader->use();
    _postShader->set_uniform("u_TexColorBuffer", 2); // cb1
    _postShader->set_uniform("u_TexBloomBuffer", 3); // cb2
}

void Demo::draw(Window& w, double p)
{
    _framebuffer->attach_color(*_colorBuffer1, 0);
    _framebuffer->attach_color(*_colorBuffer2, 1);
    std::vector<unsigned int> b = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
    w.set_framebuffer(*_framebuffer, &b);
    w.clear();
    _geomShader->use();

    // set the view matrix to the camera
    _geomShader->set_uniform("u_ViewProjMatrix", _projMatrix * _camera.get_view_matrix());
    _geomShader->set_uniform("u_CameraPosition", _camera.get_position());

    // draw a flat rectangle
    Mat4f modelMatrix = Mat4f::translation(Vec3f(0.0f, -1.05f, 0.0f)) * Mat4f::scale(Vec3f(2.0f, 0.1f, 2.0f));
    _geomShader->set_uniform("u_ModelMatrix", modelMatrix);
    _geomShader->set_uniform("u_NormalMatrix", normal_matrix(modelMatrix));
    _geomShader->set_uniform("u_TexDiffuse", 0);
    _geomShader->set_uniform("u_Diffuse", Vec3f(0.1f, 0.1f, 0.1f));
    _geomShader->set_uniform("u_Emissive", Vec3f(0.0f));
    _geomShader->set_uniform("u_Specular", Vec3f(1.0f));
    _geomShader->set_uniform("u_Shininess", 1000.0f);
    _cubeMesh->render();

    // draw a floating sphere
    double x = sin(DEG_TO_RAD(_counter * 2.0));
    double y = sin(DEG_TO_RAD(_counter));
    double z = cos(DEG_TO_RAD(_counter * 2.0));
    modelMatrix = Mat4f::translation(Vec3f(x, y + 0.5f, z));
    _geomShader->set_uniform("u_ModelMatrix", modelMatrix);
    _geomShader->set_uniform("u_NormalMatrix", normal_matrix(modelMatrix));
    _geomShader->set_uniform("u_TexDiffuse", 1);
    _geomShader->set_uniform("u_Diffuse", Vec3f(0.0f));
    _geomShader->set_uniform("u_Emissive", Vec3f(0.0f));
    _geomShader->set_uniform("u_Specular", Vec3f(0.0f));
    _sphereMesh->render();

    // draw circling light spheres
    _geomShader->set_uniform("u_TexDiffuse", 0);
    _geomShader->set_uniform("u_Diffuse", Vec3f(0.0f));
    _geomShader->set_uniform("u_Specular", Vec3f(0.0f));

    x = sin(DEG_TO_RAD(_counter * 0.25)) * 2.0;
    z = cos(DEG_TO_RAD(_counter * 0.25)) * 2.0;
    modelMatrix = Mat4f::translation(Vec3f(x, 0.5f, z)) * Mat4f::scale(Vec3f(0.25f));
    _geomShader->set_uniform("u_ModelMatrix", modelMatrix);
    _geomShader->set_uniform("u_NormalMatrix", normal_matrix(modelMatrix));
    _geomShader->set_uniform("u_Emissive", POINT_0_COLOR);
    _sphereMesh->render();
    _geomShader->set_uniform("u_PointLights[0].position", Vec3f(x, 0.5f, z));

    x = sin(DEG_TO_RAD(_counter * 0.25 + 120.0)) * 2.0;
    z = cos(DEG_TO_RAD(_counter * 0.25 + 120.0)) * 2.0;
    modelMatrix = Mat4f::translation(Vec3f(x, 0.5f, z)) * Mat4f::scale(Vec3f(0.25f));
    _geomShader->set_uniform("u_ModelMatrix", modelMatrix);
    _geomShader->set_uniform("u_NormalMatrix", normal_matrix(modelMatrix));
    _geomShader->set_uniform("u_Emissive", POINT_1_COLOR);
    _sphereMesh->render();
    _geomShader->set_uniform("u_PointLights[1].position", Vec3f(x, 0.5f, z));

    x = sin(DEG_TO_RAD(_counter * 0.25 + 240.0)) * 2.0;
    z = cos(DEG_TO_RAD(_counter * 0.25 + 240.0)) * 2.0;
    modelMatrix = Mat4f::translation(Vec3f(x, 0.5f, z)) * Mat4f::scale(Vec3f(0.25f));
    _geomShader->set_uniform("u_ModelMatrix", modelMatrix);
    _geomShader->set_uniform("u_NormalMatrix", normal_matrix(modelMatrix));
    _geomShader->set_uniform("u_Emissive", POINT_2_COLOR);
    _sphereMesh->render();
    _geomShader->set_uniform("u_PointLights[2].position", Vec3f(x, 0.5f, z));

    // skybox
    glDisable(GL_CULL_FACE);
    glDepthFunc(GL_LEQUAL);
    w.set_framebuffer(*_framebuffer);
    _skyboxShader->use();
    Mat4f cam = Mat4f(topleft(_camera.get_view_matrix()));
    _skyboxShader->set_uniform("u_ViewProjMatrix", _projMatrix * cam);
    _cubeMesh->render();
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LESS);

    // bloom
    _bloomShader->use();
    for (unsigned int i = 0; i < 4; ++i) {
        _framebuffer->attach_color(*_colorBuffer3, 0);
        w.set_framebuffer(*_framebuffer);
        _bloomShader->set_uniform("u_Horizontal", 0);
        _bloomShader->set_uniform("u_TexBrightBuffer", 3); // cb2, containing bright output
        w.clear();
        _squareMesh->render();

        _framebuffer->attach_color(*_colorBuffer2, 0);
        w.set_framebuffer(*_framebuffer);
        _bloomShader->set_uniform("u_Horizontal", 1);
        _bloomShader->set_uniform("u_TexBrightBuffer", 4); // cb3, containing previous results
        w.clear();
        _squareMesh->render();
    }

    // final pass
    w.reset_framebuffer();
    w.clear();
    _postShader->use();
    _squareMesh->render();

    ++_counter;
}

void Demo::on_key(Window&, int key, int, int act, int)
{
}

void Demo::on_mouse_move(Window&, const Vec2d& p, const Vec2d& r)
{
}
