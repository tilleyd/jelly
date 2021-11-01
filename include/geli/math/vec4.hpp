#ifndef _GELI_MATH_Vec4_HPP_
#define _GELI_MATH_Vec4_HPP_

#include <cmath>

#include <geli/math/vec2.hpp>
#include <geli/math/vec3.hpp>

namespace geli {

class Vec4 {

public:

    Vec4() : _data{0, 0, 0, 0} {}

    Vec4(float v) : _data{v, v, v, v} {}

    Vec4(float x, float y, float z, float w) : _data{x, y, z, w} {}

    Vec4(const Vec3& xyz, float w) : _data{xyz.x(), xyz.y(), xyz.z(), w} {}

    float* data() { return _data; }
    const float* data() const { return _data; }

    float& x() { return _data[0]; }
    float x() const { return _data[0]; }
    float& y() { return _data[1]; }
    float y() const { return _data[1]; }
    float& z() { return _data[2]; }
    float z() const { return _data[2]; }
    float& w() { return _data[3]; }
    float w() const { return _data[3]; }

    Vec3 xyz() const { return Vec3(x(), y(), z()); }

private:

    float _data[4];

};


/**
 * Vector-vector addition.
 */
Vec4 operator+(const Vec4& a, const Vec4& b);

/**
 * Vector-vector subtraction.
 */
Vec4 operator-(const Vec4& a, const Vec4& b);

/**
 * Vector negation, equivalent to -1 * v.
 */
Vec4 operator-(const Vec4& v);

/**
 * Scalar-vector multiplication.
 */
Vec4 operator*(float s, const Vec4& v);

/**
 * Vector-scalar multiplication.
 */
Vec4 operator*(const Vec4& v, float s);

/**
 * Vector distance, ||b - a||.
 */
float distance(const Vec4& a, const Vec4& b);

/**
 * Vector magnitude, ||v||.
 */
float magnitude(const Vec4& v);

/**
 * Dot product, a dot b.
 */
Vec4 dot(const Vec4& a, const Vec4& b);

/**
 * Normalized vector, v/||v||.
 *
 * \warn The magnitude is not checked to be non-zero.
 */
Vec4 normalize(const Vec4& v);

};

#endif
