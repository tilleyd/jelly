#ifndef _GELI_LIGHT_HPP_
#define _GELI_LIGHT_HPP_

#include <geli/math/vec3.hpp>
#include <geli/math/mat4.hpp>

namespace geli
{

/**
 * Defines a light that can be attached to renderables.
 *
 * \note All setters return a reference to the light for convenient chaining.
 */
class Light
{

public:

    enum class Type
    {
        DIRECTIONAL,
        POINT,
        SPOT
    };

    /**
     * Creates a light of the given type.
     */
    Light(Type t);

    Type get_type() const { return _type; }

    Light& set_color(const Vec3f&);

    Vec3f get_color() const { return _color; }

    Light& set_local_position(const Vec3f&);

    Vec3f get_local_position() const { return _localPosition; }

    Light& set_local_direction(const Vec3f&);

    Vec3f get_local_direction() const { return _localDirection; }

    Vec3f get_world_position() const { return _worldPosition; }

    Vec3f get_world_direction() const { return _worldDirection; }

    /**
     * Sets the attenuation factors.
     *
     * \param c
     *     Constant attenuation factor.
     * \param l
     *     Linear attenuation factor.
     * \param q
     *     Quadratic attenuation factor.
     */
    Light& set_attenuation(float c, float l, float q);

    float get_attenuation_constant() const { return _constant; }

    float get_attenuation_linear() const { return _linear; }

    float get_attenuation_quadratic() const { return _quadratic; }

private:

    friend class Renderable;

    /**
     * Updates the world position and direction.
     *
     * \param m
     *     The parent renderable's world transform.
     */
    void _update_world_transform(const Mat4f& m);

    Type _type;
    Vec3f _localPosition;
    Vec3f _localDirection;

    Vec3f _worldPosition;
    Vec3f _worldDirection;
    bool  _dirty;

    Vec3f _color;
    float _constant;
    float _linear;
    float _quadratic;

};

};

#endif
