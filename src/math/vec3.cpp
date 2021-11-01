#include <geli/math/vec3.hpp>

#include <cmath>

namespace geli {


Vec3 operator+(const Vec3& a, const Vec3& b) {
    return Vec3(a.x() + b.x(), a.y() + b.y(), a.z() + b.z());
}


Vec3 operator-(const Vec3& a, const Vec3& b) {
    return Vec3(a.x() - b.x(), a.y() - b.y(), a.z() - b.z());
}


Vec3 operator-(const Vec3& v) {
    return Vec3(-v.x(), -v.y(), -v.z());
}


Vec3 operator*(float s, const Vec3& v) {
    return Vec3(s*v.x(), s*v.y(), s*v.z());
}


Vec3 operator*(const Vec3& v, float s) {
    return Vec3(v.x()*s, v.y()*s, v.z()*s);
}


float distance(const Vec3& a, const Vec3& b) {
    return magnitude(b - a);
}


float magnitude(const Vec3& v) {
    return sqrtf(v.x()*v.x() + v.y()*v.y() + v.z()*v.z());
}


Vec3 dot(const Vec3& a, const Vec3& b) {
    return a.x()*b.x() + a.y()*b.y() + a.z()*b.z();
}


Vec3 normalize(const Vec3& v) {
    return (1.0f/magnitude(v)) * v;
}


Vec3 cross(const Vec3& a, const Vec3& b) {
    return Vec3(
        a.y()*b.z() - a.z()*b.y(),
        a.z()*b.x() - a.x()*b.z(),
        a.x()*b.y() - a.y()*b.x()
    );
}


}
