#ifndef _GELI_MATH_VEC2_HPP_
#define _GELI_MATH_VEC2_HPP_

#include <cmath>

namespace geli
{

template <typename T>
class Vec2
{

public:

    Vec2() : _data{0, 0} {};

    Vec2(T v) : _data{v, v} {};

    Vec2(T x, T y) : _data{x, y} {};

    T* data() { return _data; }
    const T* data() const { return _data; }

    T& x() { return _data[0]; }
    T x() const { return _data[0]; }
    T& y() { return _data[1]; }
    T y() const { return _data[1]; }

    Vec2<T> yx() const { return Vec2(y(), x()); }

private:

    T _data[2];

};

typedef Vec2<double> Vec2d;
typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;

/**
 * Vector-vector addition.
 */
template <typename T>
Vec2<T> operator+(const Vec2<T>& a, const Vec2<T>& b)
{
    return Vec2<T>(a.x() + b.x(), a.y() + b.y());
}

/**
 * Vector-vector subtraction.
 */
template <typename T>
Vec2<T> operator-(const Vec2<T>& a, const Vec2<T>& b)
{
    return Vec2<T>(a.x() - b.x(), a.y() - b.y());
}

/**
 * Vector negation, equivalent to -1 * v.
 */
template <typename T>
Vec2<T> operator-(const Vec2<T>& v)
{
    return Vec2<T>(-v.x(), -v.y());
}

/**
 * Scalar-vector multiplication.
 */
template <typename T>
Vec2<T> operator*(T s, const Vec2<T>& v)
{
    return Vec2<T>(s*v.x(), s*v.y());
}

/**
 * Vector-scalar multiplication.
 */
template <typename T>
Vec2<T> operator*(const Vec2<T>& v, T s)
{
    return Vec2<T>(v.x()*s, v.y()*s);
}

/**
 * Vector distance, ||b - a||.
 */
template <typename T>
float distance(const Vec2<T>& a, const Vec2<T>& b)
{
    return magnitude(b - a);
}

/**
 * Vector magnitude, ||v||.
 */
template <typename T>
float magnitude(const Vec2<T>& v)
{
    return sqrtf(static_cast<float>(v.x()*v.x() + v.y()*v.y()));
}

/**
 * Dot product, a dot b.
 */
template <typename T>
Vec2<T> dot(const Vec2<T>& a, const Vec2<T>& b)
{
    return a.x()*b.x() + a.y()*b.y();
}

/**
 * Normalized vector, v/||v||.
 *
 * \warn The magnitude is not checked to be non-zero.
 */
template <typename T>
Vec2<T> normalize(const Vec2<T>& v)
{
    return (1.0f/magnitude(v)) * v;
}

};

#endif
