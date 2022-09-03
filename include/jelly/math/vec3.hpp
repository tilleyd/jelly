#ifndef _JELLY_MATH_VEC3_HPP_
#define _JELLY_MATH_VEC3_HPP_

#include <cmath>

#include <jelly/math/vec2.hpp>

namespace jelly
{

class Vec3
{

public:

    Vec3() : _data{0, 0, 0} {};

    Vec3(float v) : _data{v, v, v} {};

    Vec3(float x, float y, float z) : _data{x, y, z} {};

    Vec3(const Vec2 xy, float z) : _data{xy.x(), xy.y(), z} {}

    Vec3(float x, const Vec2 yz) : _data{x, yz.x(), yz.y()} {}

    float* data() { return _data; }
    const float* data() const { return _data; }

    float& x() { return _data[0]; }
    float x() const { return _data[0]; }
    float& y() { return _data[1]; }
    float y() const { return _data[1]; }
    float& z() { return _data[2]; }
    float z() const { return _data[2]; }

    Vec2 xy() const { return Vec2(x(), y()); }
    Vec2 xz() const { return Vec2(x(), z()); }
    Vec2 yx() const { return Vec2(y(), x()); }
    Vec2 yz() const { return Vec2(y(), z()); }
    Vec2 zx() const { return Vec2(z(), x()); }
    Vec2 zy() const { return Vec2(z(), y()); }

    Vec3 xzy() const { return Vec3(x(), z(), y()); }
    Vec3 yxz() const { return Vec3(y(), x(), z()); }
    Vec3 yzx() const { return Vec3(y(), z(), x()); }
    Vec3 zxy() const { return Vec3(z(), x(), y()); }
    Vec3 zyx() const { return Vec3(z(), y(), x()); }

private:

    float _data[3];

};


/**
 * Vector-vector addition.
 */
Vec3 operator+(const Vec3& a, const Vec3& b);

/**
 * Vector-vector subtraction.
 */
Vec3 operator-(const Vec3& a, const Vec3& b);

/**
 * Vector negation, equivalent to -1 * v.
 */
Vec3 operator-(const Vec3& v);

/**
 * Scalar-vector multiplication.
 */
Vec3 operator*(float s, const Vec3& v);

/**
 * Vector-scalar multiplication.
 */
Vec3 operator*(const Vec3& v, float s);

/**
 * Vector distance, ||b - a||.
 */
float distance(const Vec3& a, const Vec3& b);

/**
 * Vector magnitude, ||v||.
 */
float magnitude(const Vec3& v);

/**
 * Dot product, a dot b.
 */
Vec3 dot(const Vec3& a, const Vec3& b);

/**
 * Normalized vector, v/||v||.
 *
 * \warn The magnitude is not checked to be non-zero.
 */
Vec3 normalize(const Vec3& v);

/**
 * Cross product, a cross b.
 */
Vec3 cross(const Vec3& a, const Vec3& b);

};

#endif
