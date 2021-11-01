#include <geli/math/mat4.hpp>

#include <cmath>

namespace geli {


Mat4 Mat4::perspective(float fov, float ratio, float n, float f) {
    float t = n * tanf(fov * 0.5f);
    float b = -t;
    float r = t * ratio;
    float l = -r;
    float m[] = {
         2.0f*n/(r-l),   0.0f,            0.0f,           0.0f,
         0.0f,           2.0f*n/(t-b),    0.0f,           0.0f,
         0.0f,           0.0f,           -(f+n)/(f-n),   -1.0f,
        -n*(r+l)/(r-l), -n*(t+b)/(t-b),   2.0f*f*n/(n-f), 0.0f
    };
    return Mat4(m);
}


Mat4 Mat4::orthographic(float l, float r, float b, float t, float n, float f) {
    float m[] = {
         2.0f/(r-l),   0.0f,         0.0f,        0.0f,
         0.0f,         2.0f/(t-b),   0.0f,        0.0f,
         0.0f,         0.0f,        -2.0f/(f-n),  0.0f,
        -(r+l)/(r-l), -(t+b)/(t-b), -(f+n)/(f-n), 1.0f
    };
    return Mat4(m);
}


Mat4 Mat4::look_at(const Vec3& origin, const Vec3& target, const Vec3& up) {
    Vec3 dir = normalize(origin - target);
    Vec3 right = normalize(cross(up, dir));
    Vec3 new_up = cross(dir, right);

    Mat4 rotation;
    rotation(0, 0) = right.x();
    rotation(0, 1) = right.y();
    rotation(0, 2) = right.z();
    rotation(1, 0) = new_up.x();
    rotation(1, 1) = new_up.y();
    rotation(1, 2) = new_up.z();
    rotation(2, 0) = dir.x();
    rotation(2, 1) = dir.y();
    rotation(2, 2) = dir.z();
    rotation(3, 3) = 1.0f;

    return rotation * Mat4::translation(-origin);
}


Mat4 Mat4::translation(const Vec3& t) {
    float m[] = {
        1.0f,  0.0f,  0.0f,  0.0f,
        0.0f,  1.0f,  0.0f,  0.0f,
        0.0f,  0.0f,  1.0f,  0.0f,
        t.x(), t.y(), t.z(), 1.0f
    };
    return Mat4(m);
}


Mat4 Mat4::x_rotation(float a) {
    float cs = cosf(a);
    float sn = sinf(a);
    float m[] = {
        1.0f,  0.0f, 0.0f, 0.0f,
        0.0f,  cs,   sn,   0.0f,
        0.0f, -sn,   cs,   0.0f,
        0.0f,  0.0f, 0.0f, 1.0f
    };
    return Mat4(m);
}


Mat4 Mat4::y_rotation(float a) {
    float cs = cosf(a);
    float sn = sinf(a);
    float m[] = {
        cs,   0.0f, -sn,   0.0f,
        0.0f, 1.0f,  0.0f, 0.0f,
        sn,   0.0f,  cs,   0.0f,
        0.0f, 0.0f,  0.0f, 1.0f
    };
    return Mat4(m);
}


Mat4 Mat4::z_rotation(float a) {
    float cs = cosf(a);
    float sn = sinf(a);
    float m[] = {
         cs,   sn,   0.0f, 0.0f,
        -sn,   cs,   0.0f, 0.0f,
         0.0f, 0.0f, 1.0f, 0.0f,
         0.0f, 0.0f, 0.0f, 1.0f
    };
    return Mat4(m);
}


Mat4 Mat4::scale(Vec3 s) {
    float m[] = {
        s.x(), 0.0f,  0.0f,  0.0f,
        0.0f,  s.y(), 0.0f,  0.0f,
        0.0f,  0.0f,  s.z(), 0.0f,
        0.0f,  0.0f,  0.0f,  1.0f
    };
    return Mat4(m);
}


Mat4 operator*(const Mat4& m1, const Mat4& m2) {
    // Cache-coherent multiplication as done by glm
    const float* a = m1.data();
    const float* b = m2.data();
    Mat4 result;
    float* o = result.data();

    float a00 = a[0];
    float a10 = a[1];
    float a20 = a[2];
    float a30 = a[3];
    float a01 = a[4];
    float a11 = a[5];
    float a21 = a[6];
    float a31 = a[7];
    float a02 = a[8];
    float a12 = a[9];
    float a22 = a[10];
    float a32 = a[11];
    float a03 = a[12];
    float a13 = a[13];
    float a23 = a[14];
    float a33 = a[15];

    for (unsigned int col = 0; col < 4; ++col) {
        unsigned int i1 = col*4;
        unsigned int i2 = i1+1;
        unsigned int i3 = i1+2;
        unsigned int i4 = i1+3;
        float b0 = b[i1];
        float b1 = b[i2];
        float b2 = b[i3];
        float b3 = b[i4];
        o[i1] = a00*b0 + a01*b1 + a02*b2 + a03*b3;
        o[i2] = a10*b0 + a11*b1 + a12*b2 + a13*b3;
        o[i3] = a20*b0 + a21*b1 + a22*b2 + a23*b3;
        o[i4] = a30*b0 + a31*b1 + a32*b2 + a33*b3;
    }

    return result;
}


Vec4 operator*(const Mat4& m, const Vec4& v) {
    const float* a = m.data();
    const float* b = v.data();

    float v0 = v.x();
    float v1 = v.y();
    float v2 = v.z();
    float v3 = v.w();

    return Vec4(
        m[0]*v0 + m[4]*v1 + m[8]*v2 + m[12]*v3,
        m[1]*v0 + m[5]*v1 + m[9]*v2 + m[13]*v3,
        m[2]*v0 + m[6]*v1 + m[10]*v2 + m[14]*v3,
        m[3]*v0 + m[7]*v1 + m[11]*v2 + m[15]*v3
    );
}


Mat4 operator*(float s, const Mat4& m) {
    const float* a = m.data();
    Mat4 result;
    float* o = result.data();
    for (unsigned int i = 0; i < 16; ++i) {
        o[i] = s * a[i];
    }
    return result;
}


Mat4 operator*(const Mat4& m, float s) {
    const float* a = m.data();
    Mat4 result;
    float* o = result.data();
    for (unsigned int i = 0; i < 16; ++i) {
        o[i] = a[i] * s;
    }
    return result;
}


Mat3 topleft(const Mat4& m) {
    const float* a = m.data();
    Mat3 result;
    float* o = result.data();

    o[0] = a[0];
    o[1] = a[1];
    o[2] = a[2];
    o[3] = a[4];
    o[4] = a[5];
    o[5] = a[6];
    o[6] = a[8];
    o[7] = a[9];
    o[8] = a[10];

    return result;
}


Mat3 normal_matrix(const Mat4& m) {
    return transposed_inverse(topleft(m));
}


Mat4 transpose(const Mat4& m) {
    Mat4 result;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result(j, i) = m(i, j);
        }
    }

    return result;
}

}
