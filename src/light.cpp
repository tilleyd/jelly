#include <geli/light.hpp>

using namespace geli;

Light::Light(Type t) :
    _type(t),
    _localDirection(0.0f, 0.0f, 1.0f),
    _worldDirection(0.0f, 0.0f, 1.0f),
    _dirty(false),
    _color(1.0f),
    _constant(0.0f),
    _linear(0.0f),
    _quadratic(0.0f)
{}

Light& Light::set_color(const Vec3f& v)
{
    _color = v;
    return *this;
}

Light& Light::set_local_position(const Vec3f& v)
{
    _localPosition = v;
    _dirty = true;
    return *this;
}

Light& Light::set_local_direction(const Vec3f& v)
{
    _localDirection = v;
    _dirty = true;
    return *this;
}

Light& Light::set_attenuation(float c, float l, float q)
{
    _constant = c;
    _linear = l;
    _quadratic = q;
    return *this;
}

void Light::_update_world_transform(const Mat4f& m)
{
    _worldPosition = (m * Vec4f(_localPosition, 1.0f)).xyz();
    _worldDirection = topleft(m) * _localDirection;

    _dirty = false;
}
