#include <jelly/math/vec2.hpp>

#include <cmath>

namespace jelly {


Vec2 operator+(const Vec2& a, const Vec2& b) {
    return Vec2(a.x() + b.x(), a.y() + b.y());
}


Vec2 operator-(const Vec2& a, const Vec2& b) {
    return Vec2(a.x() - b.x(), a.y() - b.y());
}


Vec2 operator-(const Vec2& v) {
    return Vec2(-v.x(), -v.y());
}


Vec2 operator*(float s, const Vec2& v) {
    return Vec2(s*v.x(), s*v.y());
}


Vec2 operator*(const Vec2& v, float s) {
    return Vec2(v.x()*s, v.y()*s);
}


float distance(const Vec2& a, const Vec2& b) {
    return magnitude(b - a);
}


float magnitude(const Vec2& v) {
    return sqrtf(v.x()*v.x() + v.y()*v.y());
}


Vec2 dot(const Vec2& a, const Vec2& b) {
    return a.x()*b.x() + a.y()*b.y();
}


Vec2 normalize(const Vec2& v) {
    return (1.0f/magnitude(v)) * v;
}


}
