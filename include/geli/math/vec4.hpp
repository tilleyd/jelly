#ifndef _GELI_MATH_Vec4_HPP_
#define _GELI_MATH_Vec4_HPP_

#include <cmath>

#include <geli/math/vec2.hpp>
#include <geli/math/vec3.hpp>

namespace geli
{

template <typename T>
class Vec4
{

public:

    Vec4() : _data{0, 0, 0, 0} {}

    Vec4(T v) : _data{v, v, v, v} {}

    Vec4(T x, T y, T z, T w) : _data{x, y, z, w} {}

    Vec4(const Vec3<T>& xyz, T w) : _data{xyz.x(), xyz.y(), xyz.z(), w} {}

    T* data() { return _data; }
    const T* data() const { return _data; }

    T& x() { return _data[0]; }
    T x() const { return _data[0]; }
    T& y() { return _data[1]; }
    T y() const { return _data[1]; }
    T& z() { return _data[2]; }
    T z() const { return _data[2]; }
    T& w() { return _data[3]; }
    T w() const { return _data[3]; }

    Vec3<T> xyz() const { return Vec3<T>(x(), y(), z()); }

private:

    T _data[4];

};

typedef Vec4<double> Vec4d;
typedef Vec4<float> Vec4f;
typedef Vec4<int> Vec4i;

/**
 * Vector-vector addition.
 */
template <typename T>
Vec4<T> operator+(const Vec4<T>& a, const Vec4<T>& b)
{
    return Vec4<T>(a.x() + b.x(), a.y() + b.y(), a.z() + b.z(), a.w() + b.w());
}

/**
 * Vector-vector subtraction.
 */
template <typename T>
Vec4<T> operator-(const Vec4<T>& a, const Vec4<T>& b)
{
    return Vec4<T>(a.x() - b.x(), a.y() - b.y(), a.z() - b.z(), a.w() - b.w());
}

/**
 * Vector negation, equivalent to -1 * v.
 */
template <typename T>
Vec4<T> operator-(const Vec4<T>& v)
{
    return Vec4<T>(-v.x(), -v.y(), -v.z(), -v.w());
}

/**
 * Scalar-vector multiplication.
 */
template <typename T>
Vec4<T> operator*(T s, const Vec4<T>& v)
{
    return Vec4<T>(s*v.x(), s*v.y(), s*v.z(), s*v.w());
}

/**
 * Vector-scalar multiplication.
 */
template <typename T>
Vec4<T> operator*(const Vec4<T>& v, T s)
{
    return Vec4<T>(v.x()*s, v.y()*s, v.z()*s, v.w()*s);
}

/**
 * Vector distance, ||b - a||.
 */
template <typename T>
float distance(const Vec4<T>& a, const Vec4<T>& b)
{
    return magnitude(b - a);
}

/**
 * Vector magnitude, ||v||.
 */
template <typename T>
float magnitude(const Vec4<T>& v)
{
    return sqrtf(static_cast<float>(v.x()*v.x() + v.y()*v.y() + v.z()*v.z() + v.w()*v.w()));
}

/**
 * Dot product, a dot b.
 */
template <typename T>
Vec4<T> dot(const Vec4<T>& a, const Vec4<T>& b)
{
    return a.x()*b.x() + a.y()*b.y() + a.z()*b.z() + a.w()*b.w();
}

/**
 * Normalized vector, v/||v||.
 *
 * \warn The magnitude is not checked to be non-zero.
 */
template <typename T>
Vec4<T> normalize(const Vec4<T>& v)
{
    return (1.0f/magnitude(v)) * v;
}

};

#endif
