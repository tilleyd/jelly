#ifndef _GELI_MATH_VEC2_HPP_
#define _GELI_MATH_VEC2_HPP_

namespace geli
{

template <typename T>
class Vec2
{

public:

    Vec2() : _data{0, 0} {};

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

};

#endif
