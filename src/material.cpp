#include <geli/material.hpp>

#include <geli/shader.hpp>

using namespace geli;

std::shared_ptr<Texture> Material::_texEmpty;

void Material::apply(std::shared_ptr<Shader> shader)
{
    shader->set_uniform("u_Diffuse", _diffuse);
    shader->set_uniform("u_Emissive", _emissive);
    shader->set_uniform("u_Specular", _specular);
    shader->set_uniform("u_Shininess", _shininess);

    // create the empty texture if it doesn't exist
    if (!_texEmpty) {
        _texEmpty = std::make_shared<Texture>(Vec3f(0.0f));
    }

    if (_texDiffuse) {
        _texDiffuse->bind(0);
    } else {
        _texEmpty->bind(0);
    }
    if (_texEmissive) {
        _texEmissive->bind(1);
    } else {
        _texEmpty->bind(1);
    }
    if (_texSpecular) {
        _texSpecular->bind(2);
    } else {
        _texEmpty->bind(2);
    }
    if (_texShininess) {
        _texShininess->bind(3);
    } else {
       _texEmpty->bind(3);
    }
}
