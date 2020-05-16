#ifndef _GELI_MATH_VEC3_HPP_
#define _GELI_MATH_VEC3_HPP_

#include <geli/math/vec2.hpp>

namespace geli
{

template <typename T>
class Vec3
{

public:

    Vec3() : _data{0, 0} {};

    Vec3(T x, T y, T z) : _data{x, y, z} {};

    Vec3(const Vec2 xy, T z) : _data{xy.x(), xy.y(), z} {}

    Vec3(T x, const Vec2 yz) : _data{x, yz.y(), yz.z()} {}

    T& x() { return _data[0]; }
    T& y() { return _data[1]; }
    T& z() { return _data[2]; }

    Vec2<T> xy() { return Vec2<T>(x(), y()); }
    Vec2<T> xz() { return Vec2<T>(x(), z()); }
    Vec2<T> yx() { return Vec2<T>(y(), x()); }
    Vec2<T> yz() { return Vec2<T>(y(), z()); }
    Vec2<T> zx() { return Vec2<T>(z(), x()); }
    Vec2<T> zy() { return Vec2<T>(z(), y()); }

    Vec3<T> xzy() { return Vec3<T>(x(), z(), y()); }
    Vec3<T> yxz() { return Vec3<T>(y(), x(), z()); }
    Vec3<T> yzx() { return Vec3<T>(y(), z(), x()); }
    Vec3<T> zxy() { return Vec3<T>(z(), x(), y()); }
    Vec3<T> zyx() { return Vec3<T>(z(), y(), x()); }

private:

    T _data[2];

};

typedef Vec3<double> Vec3d;
typedef Vec3<float> Vec3f;
typedef Vec3<int> Vec3i;

};

#endif
