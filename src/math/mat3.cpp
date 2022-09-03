#include <jelly/math/mat3.hpp>

#include <cmath>

namespace jelly {


Mat3 operator*(const Mat3& m1, const Mat3& m2)
{
    const float* a = m1.data();
    const float* b = m2.data();
    Mat3 result;
    float* o = result.data();

    float a00 = a[0];
    float a10 = a[1];
    float a20 = a[2];
    float a01 = a[3];
    float a11 = a[4];
    float a21 = a[5];
    float a02 = a[6];
    float a12 = a[7];
    float a22 = a[8];
    for (unsigned int col = 0; col < 3; ++col) {
        unsigned int i1 = col*3;
        unsigned int i2 = i1+1;
        unsigned int i3 = i1+2;
        float b0 = b[i1];
        float b1 = b[i2];
        float b2 = b[i3];
        o[i1] = a00 * b0 + a01 * b1 + a02 * b2;
        o[i2] = a10 * b0 + a11 * b1 + a12 * b2;
        o[i3] = a20 * b0 + a21 * b1 + a22 * b2;
    }

    return result;
}


Vec3 operator*(const Mat3& m, const Vec3& v)
{
    const float* a = m.data();
    const float* b = v.data();

    float v0 = v.x();
    float v1 = v.y();
    float v2 = v.z();

    return Vec3(
        m[0]*v0 + m[4]*v1 + m[8]*v2,
        m[1]*v0 + m[5]*v1 + m[9]*v2,
        m[2]*v0 + m[6]*v1 + m[10]*v2
    );
}


Mat3 operator*(float s, const Mat3& m)
{
    const float* a = m.data();
    Mat3 result;
    float* o = result.data();
    for (unsigned int i = 0; i < 9; ++i) {
        o[i] = s * a[i];
    }
    return result;
}


Mat3 operator*(const Mat3& m, float s)
{
    const float* a = m.data();
    Mat3 result;
    float* o = result.data();
    for (unsigned int i = 0; i < 9; ++i) {
        o[i] = a[i] * s;
    }
    return result;
}


float determinant(const Mat3& m)
{
    float d1 = m(0, 0) * (m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1));
    float d2 = m(0, 1) * (m(1, 0) * m(2, 2) - m(1, 2) * m(2, 0));
    float d3 = m(0, 2) * (m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0));
    return d1 - d2 + d3;
}


Mat3 transpose(const Mat3& m)
{
    Mat3 result;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result(j, i) = m(i, j);
        }
    }

    return result;
}


Mat3 transposed_inverse(const Mat3& m)
{
    Mat3 result;
    float* o = result.data();

    float det = determinant(m);

    o[0] = + (m(1, 1) * m(2, 2) - m(2, 1) * m(1, 2));
    o[1] = - (m(1, 0) * m(2, 2) - m(2, 0) * m(1, 2));
    o[2] = + (m(1, 0) * m(2, 1) - m(2, 0) * m(1, 1));
    o[3] = - (m(0, 1) * m(2, 2) - m(2, 1) * m(0, 2));
    o[4] = + (m(0, 0) * m(2, 2) - m(2, 0) * m(0, 2));
    o[5] = - (m(0, 0) * m(2, 1) - m(2, 0) * m(0, 1));
    o[6] = + (m(0, 1) * m(1, 2) - m(1, 1) * m(0, 2));
    o[7] = - (m(0, 0) * m(1, 2) - m(1, 0) * m(0, 2));
    o[8] = + (m(0, 0) * m(1, 1) - m(1, 0) * m(0, 1));

    return result * (1.0f/det);
}


}
