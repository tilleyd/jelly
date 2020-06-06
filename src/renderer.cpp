#include <geli/renderer.hpp>

#include <string>

#include <geli/window.hpp>

using namespace geli;

Renderer::Renderer(Window* w) :
    _projMatrix(1.0f),
    _viewMatrix(1.0f),
    _prevPointLightCount(0),
    _prevSpotLightCount(0),
    _window(w)
{
    _root = std::shared_ptr<Renderable>(new Renderable());

    // create shaders
    _geomShader = Shader::create_single_pass_shader();
    _skyboxShader = Shader::create_skybox_shader();
    _bloomShader = Shader::create_bloom_shader();
    _postShader = Shader::create_post_shader();

    // create framebuffers
    _colorBuffer1 = std::make_shared<Texture>(w->get_size(), Texture::Format::RGB16F);
    _colorBuffer2 = std::make_shared<Texture>(w->get_size(), Texture::Format::RGB16F);
    _colorBuffer3 = std::make_shared<Texture>(w->get_size(), Texture::Format::RGB16F);
    _depthBuffer = std::make_shared<Texture>(w->get_size(), Texture::Format::DEPTH);
    _framebuffer = std::make_shared<Framebuffer>();
    _framebuffer->attach_depth(*_depthBuffer);

    // create necessary meshes
    add_mesh(Mesh::create_square_mesh());
    add_mesh(Mesh::create_cube_mesh());

    // create default material
    add_material(std::make_shared<Material>());

    // assign fixed uniforms
    _geomShader->use();
    _geomShader->set_uniform("u_TexDiffuse", 0);
    _geomShader->set_uniform("u_TexSpecular", 1);
    _geomShader->set_uniform("u_TexEmissive", 2);
    _geomShader->set_uniform("u_TexShininess", 3);
}

std::shared_ptr<Renderable> Renderer::create_renderable()
{
    return _root->create_child();
}

int Renderer::add_mesh(std::shared_ptr<Mesh> m)
{
    _meshes.push_back(m);
    return _meshes.size() - 1;
}

std::shared_ptr<Mesh> Renderer::get_mesh(int i)
{
    if (i < _meshes.size() && i > 0) {
        return _meshes[i];
    } else {
        return nullptr;
    }
}

void Renderer::set_mesh(int i, std::shared_ptr<Mesh> m)
{
    _meshes.at(i) = m;
}

int Renderer::add_material(std::shared_ptr<Material> m)
{
    _materials.push_back(m);
    return _materials.size() - 1;
}

std::shared_ptr<Material> Renderer::get_material(int i)
{
    if (i < _materials.size() && i > 0) {
        return _materials[i];
    } else {
        return nullptr;
    }
}

void Renderer::set_material(int i, std::shared_ptr<Material> m)
{
    _materials.at(i) = m;
}

void Renderer::render()
{
    render(*_root);
}

void Renderer::render(Renderable& scene)
{
    _root->update_child_world_transforms();

    // for the geometry pass, render to the first buffer and brights to the second buffer
    _framebuffer->attach_color(*_colorBuffer1, 0);
    _framebuffer->attach_color(*_colorBuffer2, 1);
    std::vector<unsigned int> b = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
    set_framebuffer(*_framebuffer, &b);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    _geomShader->use();
    _geomShader->set_uniform("u_ViewProjMatrix", _projMatrix * _viewMatrix);
    _geomShader->set_uniform("u_CameraPosition", _cameraPosition);

    unsigned int pointLightCount = 0;
    unsigned int spotLightCount = 0;

    _root->for_each([&](Renderable& r)
    {
        std::shared_ptr<Mesh> mesh = get_mesh(r.get_mesh());
        std::shared_ptr<Material> material = get_material(r.get_material());
        if (mesh) {
            _geomShader->set_uniform("u_ModelMatrix", r.get_world_transform());
            _geomShader->set_uniform("u_NormalMatrix", normal_matrix(r.get_world_transform()));

            // apply lights
            for (const Light& l : r.get_lights()) {
                switch (l.get_type()) {
                    case Light::Type::DIRECTIONAL:
                        set_directional_light(l);
                        break;
                    case Light::Type::POINT:
                        set_point_light(l, pointLightCount++);
                        break;
                    case Light::Type::SPOT:
                        set_spot_light(l, spotLightCount++);
                        break;
                }
            }

            // clear lights if there are less than previously
            for (unsigned int pl = pointLightCount; pl < _prevPointLightCount; ++pl) {
                clear_point_light(pl);
            }
            for (unsigned int sl = spotLightCount; sl < _prevSpotLightCount; ++sl) {
                clear_spot_light(sl);
            }

            // apply the material
            if (!material) material = _materials[0];
            material->apply(_geomShader);

            mesh->render();
        }
    });

    // render the skybox
    glDisable(GL_CULL_FACE);
    glDepthFunc(GL_LEQUAL);
    set_framebuffer(*_framebuffer); // only render to the first buffer
    _skyboxShader->use();
    Mat4f viewRotation = Mat4f(topleft(_viewMatrix));
    _skyboxShader->set_uniform("u_ViewProjMatrix", _projMatrix * viewRotation);
    _meshes[1]->render(); // render the cube mesh
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LESS);

    // bind the color buffers for post processing
    _colorBuffer1->bind(0);
    _colorBuffer2->bind(1);
    _colorBuffer3->bind(2);

    // blur the bright buffer for bloom effect
    _bloomShader->use();
    for (unsigned int i = 0; i < 4; ++i) {
        // ping from buffer 2 into buffer 3
        _framebuffer->attach_color(*_colorBuffer3, 0);
        set_framebuffer(*_framebuffer);
        _bloomShader->set_uniform("u_Horizontal", 0);
        _bloomShader->set_uniform("u_TexBrightBuffer", 1); // buffer 2
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        _meshes[0]->render(); // quad mesh
        // pong from buffer 3 into buffer 2
        _framebuffer->attach_color(*_colorBuffer2, 0);
        set_framebuffer(*_framebuffer);
        _bloomShader->set_uniform("u_Horizontal", 1);
        _bloomShader->set_uniform("u_TexBrightBuffer", 2); // buffer 3
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        _meshes[0]->render(); // quad mesh
    }

    // final pass
    reset_framebuffer();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    _postShader->use();
    _postShader->set_uniform("u_TexColorBuffer", 0); // buffer 1
    _postShader->set_uniform("u_TexBloomBuffer", 1); // buffer 2
    _meshes[0]->render(); // quad mesh
}

void Renderer::set_framebuffer(const Framebuffer& fb, const std::vector<unsigned int>* buffers)
{
    glBindFramebuffer(GL_FRAMEBUFFER, fb.get_handle());

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
        // leave the framebuffer bound and set remaining properties
        if (buffers) {
            glDrawBuffers(buffers->size(), buffers->data());
        } else {
            glDrawBuffer(GL_COLOR_ATTACHMENT0);
        }
    } else {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        throw std::runtime_error("attempt to use incorrectly formed framebuffer");
    }
}

void Renderer::reset_framebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
}

void Renderer::set_background_color(const Vec3f& color)
{
    glClearColor(color.x(), color.y(), color.z(), 1.0f);
}

void Renderer::set_ambient_light(const Vec3f& color)
{
    _geomShader->set_uniform("u_AmbientLight", color);
}

void Renderer::set_directional_light(const Light& l)
{
    _geomShader->set_uniform("u_DirecitonalLight.color", l.get_color());
    _geomShader->set_uniform("u_DirectionalLight.direction", l.get_world_direction());
}

void Renderer::set_point_light(const Light& l, unsigned int i)
{
    char buffer[64];
    sprintf(buffer, "u_PointLights[%d].", i);
    std::string target(buffer);
    _geomShader->set_uniform(target + "color", l.get_color());
    _geomShader->set_uniform(target + "position", l.get_world_position());
    _geomShader->set_uniform(target + "constant", l.get_attenuation_constant());
    _geomShader->set_uniform(target + "linear", l.get_attenuation_linear());
    _geomShader->set_uniform(target + "quadratic", l.get_attenuation_quadratic());
}

void Renderer::clear_point_light(unsigned int i)
{
    char buffer[64];
    sprintf(buffer, "u_PointLights[%d].color", i);
    _geomShader->set_uniform(buffer, Vec3f(0.0f));
}

void Renderer::set_spot_light(const Light& l, unsigned int i)
{
    // TODO
}

void Renderer::clear_spot_light(unsigned int i)
{
    // TODO
}
