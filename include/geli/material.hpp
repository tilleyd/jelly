#ifndef _GELI_MATERIAL_HPP_
#define _GELI_MATERIAL_HPP_

#include <memory>

#include <geli/texture.hpp>
#include <geli/math/vec3.hpp>

namespace geli
{

class Shader;

/**
 * A material with various properties. The properties define the surface
 * appearence of a mesh.
 */
class Material
{

public:

    /**
     * Creates a default black matte material.
     */
    Material() = default;

    void set_diffuse(const Vec3f& v) { _diffuse = v; }

    Vec3f get_diffuse() const { return _diffuse; }

    void set_emissive(const Vec3f& v) { _emissive = v; }

    Vec3f get_emissive() const { return _emissive; }

    void set_specular(const Vec3f& v) { _specular = v; }

    Vec3f get_specular() const { return _specular; }

    void set_shininess(float f) { _shininess = f; }

    float get_shininess() const { return _shininess; }

    void set_diffuse_texture(std::shared_ptr<Texture> t) { _texDiffuse = t; }

    std::shared_ptr<Texture> get_diffuse_texture() const { return _texDiffuse; }

    void set_emissive_texture(std::shared_ptr<Texture> t) { _texEmissive = t; }

    std::shared_ptr<Texture> get_emissive_texture() const { return _texEmissive; }

    void set_specular_texture(std::shared_ptr<Texture> t) { _texSpecular = t; }

    std::shared_ptr<Texture> get_specular_texture() const { return _texSpecular; }

    void set_shininess_texture(std::shared_ptr<Texture> t) { _texShininess = t; }

    std::shared_ptr<Texture> get_shininess_texture() const { return _texShininess; }

    /**
     * Applies the texture to the given shader. Uses the default uniform names
     * of the geli renderer. The four textures (diffuse, emissive, specular
     * and shininess) are bound to locations 0-3, respectively. The samplers
     * are assumed to be set to these locations.
     */
    void apply(std::shared_ptr<Shader>);

private:

    Vec3f _diffuse;
    Vec3f _emissive;
    Vec3f _specular;
    float _shininess;

    std::shared_ptr<Texture> _texDiffuse;
    std::shared_ptr<Texture> _texEmissive;
    std::shared_ptr<Texture> _texSpecular;
    std::shared_ptr<Texture> _texShininess;

    static std::shared_ptr<Texture> _texEmpty;

};

};

#endif
