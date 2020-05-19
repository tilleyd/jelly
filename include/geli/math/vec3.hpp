#ifndef _GELI_MATH_VEC3_HPP_
#define _GELI_MATH_VEC3_HPP_

#include <cmath>

#include <geli/math/vec2.hpp>

namespace geli
{

template <typename T>
class Vec3
{

public:

    Vec3() : _data{0, 0} {};

    Vec3(T v) : _data{v, v, v} {};

    Vec3(T x, T y, T z) : _data{x, y, z} {};

    Vec3(const Vec2<T> xy, T z) : _data{xy.x(), xy.y(), z} {}

    Vec3(T x, const Vec2<T> yz) : _data{x, yz.y(), yz.z()} {}

    T* data() { return _data; }
    const T* data() const { return _data; }

    T& x() { return _data[0]; }
    T x() const { return _data[0]; }
    T& y() { return _data[1]; }
    T y() const { return _data[1]; }
    T& z() { return _data[2]; }
    T z() const { return _data[2]; }

    Vec2<T> xy() const { return Vec2<T>(x(), y()); }
    Vec2<T> xz() const { return Vec2<T>(x(), z()); }
    Vec2<T> yx() const { return Vec2<T>(y(), x()); }
    Vec2<T> yz() const { return Vec2<T>(y(), z()); }
    Vec2<T> zx() const { return Vec2<T>(z(), x()); }
    Vec2<T> zy() const { return Vec2<T>(z(), y()); }

    Vec3<T> xzy() const { return Vec3<T>(x(), z(), y()); }
    Vec3<T> yxz() const { return Vec3<T>(y(), x(), z()); }
    Vec3<T> yzx() const { return Vec3<T>(y(), z(), x()); }
    Vec3<T> zxy() const { return Vec3<T>(z(), x(), y()); }
    Vec3<T> zyx() const { return Vec3<T>(z(), y(), x()); }

private:

    T _data[3];

};

typedef Vec3<double> Vec3d;
typedef Vec3<float> Vec3f;
typedef Vec3<int> Vec3i;

/**
 * Vector-vector addition.
 */
template <typename T>
Vec3<T> operator+(const Vec3<T>& a, const Vec3<T>& b)
{
    return Vec3<T>(a.x() + b.x(), a.y() + b.y(), a.z() + b.z());
}

/**
 * Vector-vector subtraction.
 */
template <typename T>
Vec3<T> operator-(const Vec3<T>& a, const Vec3<T>& b)
{
    return Vec3<T>(a.x() - b.x(), a.y() - b.y(), a.z() - b.z());
}

/**
 * Vector negation, equivalent to -1 * v.
 */
template <typename T>
Vec3<T> operator-(const Vec3<T>& v)
{
    return Vec3<T>(-v.x(), -v.y(), -v.z());
}

/**
 * Scalar-vector multiplication.
 */
template <typename T>
Vec3<T> operator*(T s, const Vec3<T>& v)
{
    return Vec3<T>(s*v.x(), s*v.y(), s*v.z());
}

/**
 * Vector-scalar multiplication.
 */
template <typename T>
Vec3<T> operator*(const Vec3<T>& v, T s)
{
    return Vec3<T>(v.x()*s, v.y()*s, v.z()*s);
}

/**
 * Vector distance, ||b - a||.
 */
template <typename T>
float distance(const Vec3<T>& a, const Vec3<T>& b)
{
    return magnitude(b - a);
}

/**
 * Vector magnitude, ||v||.
 */
template <typename T>
float magnitude(const Vec3<T>& v)
{
    return sqrtf(static_cast<float>(v.x()*v.x() + v.y()*v.y() + v.z()*v.z()));
}

/**
 * Dot product, a dot b.
 */
template <typename T>
Vec3<T> dot(const Vec3<T>& a, const Vec3<T>& b)
{
    return a.x()*b.x() + a.y()*b.y() + a.z()*b.z();
}

/**
 * Normalized vector, v/||v||.
 *
 * \warn The magnitude is not checked to be non-zero.
 */
template <typename T>
Vec3<T> normalize(const Vec3<T>& v)
{
    return (1.0f/magnitude(v)) * v;
}

/**
 * Cross product, a cross b.
 */
template <typename T>
Vec3<T> cross(const Vec3<T>& a, const Vec3<T>& b)
{
    return Vec3<T>(
        a.y()*b.z() - a.z()*b.y(),
        a.z()*b.x() - a.x()*b.z(),
        a.x()*b.y() - a.y()*b.x()
    );
}

};

#endif
