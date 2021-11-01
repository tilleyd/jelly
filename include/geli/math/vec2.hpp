#ifndef _GELI_MATH_VEC2_HPP_
#define _GELI_MATH_VEC2_HPP_

#include <cmath>

namespace geli {

class Vec2 {

public:

    Vec2() : _data{0, 0} {};

    Vec2(float v) : _data{v, v} {};

    Vec2(float x, float y) : _data{x, y} {};

    float* data() { return _data; }
    const float* data() const { return _data; }

    float& x() { return _data[0]; }
    float x() const { return _data[0]; }
    float& y() { return _data[1]; }
    float y() const { return _data[1]; }

    Vec2 yx() const { return Vec2(y(), x()); }

private:

    float _data[2];

};


/**
 * Vector-vector addition.
 */
Vec2 operator+(const Vec2& a, const Vec2& b);

/**
 * Vector-vector subtraction.
 */
Vec2 operator-(const Vec2& a, const Vec2& b);

/**
 * Vector negation, equivalent to -1 * v.
 */
Vec2 operator-(const Vec2& v);

/**
 * Scalar-vector multiplication.
 */
Vec2 operator*(float s, const Vec2& v);

/**
 * Vector-scalar multiplication.
 */
Vec2 operator*(const Vec2& v, float s);

/**
 * Vector distance, ||b - a||.
 */
float distance(const Vec2& a, const Vec2& b);

/**
 * Vector magnitude, ||v||.
 */
float magnitude(const Vec2& v);

/**
 * Dot product, a dot b.
 */
Vec2 dot(const Vec2& a, const Vec2& b);

/**
 * Normalized vector, v/||v||.
 *
 * \warning The magnitude is not checked to be non-zero.
 */
Vec2 normalize(const Vec2& v);

};

#endif
