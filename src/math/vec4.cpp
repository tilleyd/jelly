#include <jelly/math/vec4.hpp>

#include <cmath>

namespace jelly {


Vec4 operator+(const Vec4& a, const Vec4& b) {
    return Vec4(a.x() + b.x(), a.y() + b.y(), a.z() + b.z(), a.w() + b.w());
}


Vec4 operator-(const Vec4& a, const Vec4& b) {
    return Vec4(a.x() - b.x(), a.y() - b.y(), a.z() - b.z(), a.w() - b.w());
}


Vec4 operator-(const Vec4& v) {
    return Vec4(-v.x(), -v.y(), -v.z(), -v.w());
}


Vec4 operator*(float s, const Vec4& v) {
    return Vec4(s*v.x(), s*v.y(), s*v.z(), s*v.w());
}


Vec4 operator*(const Vec4& v, float s) {
    return Vec4(v.x()*s, v.y()*s, v.z()*s, v.w()*s);
}


float distance(const Vec4& a, const Vec4& b) {
    return magnitude(b - a);
}


float magnitude(const Vec4& v) {
    return sqrtf(v.x()*v.x() + v.y()*v.y() + v.z()*v.z() + v.w()*v.w());
}


Vec4 dot(const Vec4& a, const Vec4& b) {
    return a.x()*b.x() + a.y()*b.y() + a.z()*b.z() + a.w()*b.w();
}


Vec4 normalize(const Vec4& v) {
    return (1.0f/magnitude(v)) * v;
}


}
