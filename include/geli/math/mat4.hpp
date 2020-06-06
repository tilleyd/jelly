#ifndef _GELI_MATH_MAT4_HPP_
#define _GELI_MATH_MAT4_HPP_

#include <cmath>

#include <geli/math/vec4.hpp>
#include <geli/math/mat3.hpp>

namespace geli
{

template <typename T>
class Mat4
{

public:

    /**
     * Creates a perspective projection matrix.
     *
     * \param fov
     *     The field of view of the projection in radians.
     * \param ratio
     *     The aspect ratio of the viewport (width / height).
     * \param near
     *     The near cut-off distance.
     * \param far
     *     The far cut-off distance.
     */
    static Mat4<T> perspective(float fov, float ratio, float near, float far);

    /**
     * Creates an orthographic projection matrix.
     *
     * \param l
     *     The left side of the projection cube.
     * \param r
     *     The right side of the projection cube.
     * \param b
     *     The bottom of the projection cube.
     * \param t
     *     The top of the projection cube.
     * \param n
     *     The near side of the projection cube.
     * \param f
     *     The far side of the projection cube.
     */
    static Mat4<T> orthographic(float l, float r, float b, float t, float n, float f);

    /**
     * Creates a look-at matrix.
     *
     * \param origin
     *     The point at which the object is located.
     * \param target
     *     The point at which the look-at matrix must look.
     * \param up
     *     The up direction of the world, usually [0 1 0].
     */
    static Mat4<T> look_at(const Vec3<T>& origin, const Vec3<T>& target, const Vec3<T>& up);

    /**
     * Creates a translation matrix.
     *
     * \param t
     *     The translation vector.
     */
    static Mat4<T> translation(const Vec3<T>& t);

    /**
     * Creates an x rotation matrix.
     *
     * \param a
     *     The x rotation angle in radians.
     */
    static Mat4<T> x_rotation(float a);

    /**
     * Creates a y rotation matrix.
     *
     * \param a
     *     The y rotation angle in radians.
     */
    static Mat4<T> y_rotation(float a);

    /**
     * Creates a z rotation matrix.
     *
     * \param a
     *     The z rotation angle in radians.
     */
    static Mat4<T> z_rotation(float a);

    /**
     * Creates a scaling matrix.
     *
     * \param s
     *     The scale to apply per axis.
     */
    static Mat4<T> scale(Vec3<T> s);

    /**
     * Creates a zero Mat4.
     */
    Mat4() : _data{} {}

    /**
     * Creates a diagonal Mat4 with all diagonals set to the provided value.
     */
    Mat4(T d) : _data{d, 0, 0, 0,
                      0, d, 0, 0,
                      0, 0, d, 0,
                      0, 0, 0, d} {}

    /**
     * Creates a Mat4 from the given array.
     *
     * \note The array must be in column-major form.
     */
    Mat4(T m[16])
    {
        for (unsigned int i = 0; i < 16; ++i) _data[i] = m[i];
    }

    /**
     * Creates a Mat4 containing the Mat3 as the top-left part of the matrix
     * and w at position (3, 3).
     */
    Mat4(const Mat3<T>& m, T w = 1.0) : _data{m[0], m[1], m[2], 0,
                                              m[3], m[4], m[5], 0,
                                              m[6], m[7], m[8], 0,
                                              0,    0,    0,    w} {}

    /**
     * Returns a pointer to the matrix.
     *
     * \note The array is in column-major form.
     */
    T* data() { return _data; }

    T& operator()(unsigned int r, unsigned int c) { return _data[4*c+r]; }
    T operator()(unsigned int r, unsigned int c) const { return _data[4*c+r]; }

    T& operator[](unsigned int i) { return _data[i]; }
    T operator[](unsigned int i) const { return _data[i]; }

    /**
     * Returns a pointer to the matrix.
     *
     * \note the array is in column-major form.
     */
    const T* data() const { return _data; }

private:

    T _data[16];

};

typedef Mat4<double> Mat4d;
typedef Mat4<int> Mat4i;
typedef Mat4<float> Mat4f;

template <typename T>
Mat4<T> Mat4<T>::perspective(float fov, float ratio, float n, float f)
{
    float t = n * tanf(fov * 0.5f);
    float b = -t;
    float r = t * ratio;
    float l = -r;
    T m[] = {
         2.0f*n/(r-l),   0.0f,            0.0f,           0.0f,
         0.0f,           2.0f*n/(t-b),    0.0f,           0.0f,
         0.0f,           0.0f,           -(f+n)/(f-n),   -1.0f,
        -n*(r+l)/(r-l), -n*(t+b)/(t-b),   2.0f*f*n/(n-f), 0.0f
    };
    return Mat4<T>(m);
}

template <typename T>
Mat4<T> Mat4<T>::orthographic(float l, float r, float b, float t, float n, float f)
{
    T m[] = {
         2.0f/(r-l),   0.0f,         0.0f,        0.0f,
         0.0f,         2.0f/(t-b),   0.0f,        0.0f,
         0.0f,         0.0f,        -2.0f/(f-n),  0.0f,
        -(r+l)/(r-l), -(t+b)/(t-b), -(f+n)/(f-n), 1.0f
    };
    return Mat4<T>(m);
}

template <typename T>
Mat4<T> Mat4<T>::look_at(const Vec3<T>& origin, const Vec3<T>& target, const Vec3<T>& up)
{
    Vec3<T> dir = normalize(origin - target);
    Vec3<T> right = normalize(cross(up, dir));
    Vec3<T> new_up = cross(dir, right);

    Mat4<T> rotation;
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

    return rotation * Mat4<T>::translation(-origin);
}

template <typename T>
Mat4<T> Mat4<T>::translation(const Vec3<T>& t)
{
    T m[] = {
        1.0f,  0.0f,  0.0f,  0.0f,
        0.0f,  1.0f,  0.0f,  0.0f,
        0.0f,  0.0f,  1.0f,  0.0f,
        t.x(), t.y(), t.z(), 1.0f
    };
    return Mat4<T>(m);
}

template <typename T>
Mat4<T> Mat4<T>::x_rotation(float a)
{
    float cs = cosf(a);
    float sn = sinf(a);
    T m[] = {
        1.0f,  0.0f, 0.0f, 0.0f,
        0.0f,  cs,   sn,   0.0f,
        0.0f, -sn,   cs,   0.0f,
        0.0f,  0.0f, 0.0f, 1.0f
    };
    return Mat4<T>(m);
}

template <typename T>
Mat4<T> Mat4<T>::y_rotation(float a)
{
    float cs = cosf(a);
    float sn = sinf(a);
    T m[] = {
        cs,   0.0f, -sn,   0.0f,
        0.0f, 1.0f,  0.0f, 0.0f,
        sn,   0.0f,  cs,   0.0f,
        0.0f, 0.0f,  0.0f, 1.0f
    };
    return Mat4<T>(m);
}

template <typename T>
Mat4<T> Mat4<T>::z_rotation(float a)
{
    float cs = cosf(a);
    float sn = sinf(a);
    T m[] = {
         cs,   sn,   0.0f, 0.0f,
        -sn,   cs,   0.0f, 0.0f,
         0.0f, 0.0f, 1.0f, 0.0f,
         0.0f, 0.0f, 0.0f, 1.0f
    };
    return Mat4<T>(m);
}

template <typename T>
Mat4<T> Mat4<T>::scale(Vec3<T> s)
{
    T m[] = {
        s.x(), 0.0f,  0.0f,  0.0f,
        0.0f,  s.y(), 0.0f,  0.0f,
        0.0f,  0.0f,  s.z(), 0.0f,
        0.0f,  0.0f,  0.0f,  1.0f
    };
    return Mat4<T>(m);
}

/**
 * Matrix-matrix multiplication.
 */
template <typename T>
Mat4<T> operator*(const Mat4<T>& m1, const Mat4<T>& m2)
{
    // cache-coherent multiplication as done by glm
    const T* a = m1.data();
    const T* b = m2.data();
    Mat4<T> result;
    T* o = result.data();

    T a00 = a[0];
    T a10 = a[1];
    T a20 = a[2];
    T a30 = a[3];
    T a01 = a[4];
    T a11 = a[5];
    T a21 = a[6];
    T a31 = a[7];
    T a02 = a[8];
    T a12 = a[9];
    T a22 = a[10];
    T a32 = a[11];
    T a03 = a[12];
    T a13 = a[13];
    T a23 = a[14];
    T a33 = a[15];

    for (unsigned int col = 0; col < 4; ++col) {
        unsigned int i1 = col*4;
        unsigned int i2 = i1+1;
        unsigned int i3 = i1+2;
        unsigned int i4 = i1+3;
        T b0 = b[i1];
        T b1 = b[i2];
        T b2 = b[i3];
        T b3 = b[i4];
        o[i1] = a00*b0 + a01*b1 + a02*b2 + a03*b3;
        o[i2] = a10*b0 + a11*b1 + a12*b2 + a13*b3;
        o[i3] = a20*b0 + a21*b1 + a22*b2 + a23*b3;
        o[i4] = a30*b0 + a31*b1 + a32*b2 + a33*b3;
    }

    return result;
}

/**
 * Vector-matrix multiplication.
 */
template <typename T>
Vec4<T> operator*(const Mat4<T>& m, const Vec4<T>& v)
{
    const T* a = m.data();
    const T* b = v.data();

    T v0 = v.x();
    T v1 = v.y();
    T v2 = v.z();
    T v3 = v.w();

    return Vec4<T>(
        m[0]*v0 + m[4]*v1 + m[8]*v2 + m[12]*v3,
        m[1]*v0 + m[5]*v1 + m[9]*v2 + m[13]*v3,
        m[2]*v0 + m[6]*v1 + m[10]*v2 + m[14]*v3,
        m[3]*v0 + m[7]*v1 + m[11]*v2 + m[15]*v3
    );
    // return Vec4<T>(
    //     m[0]*v0 + m[1]*v1 + m[2]*v2 + m[3]*v3,
    //     m[4]*v0 + m[5]*v1 + m[6]*v2 + m[7]*v3,
    //     m[8]*v0 + m[9]*v1 + m[10]*v2 + m[11]*v3,
    //     m[12]*v0 + m[13]*v1 + m[14]*v2 + m[15]*v3
    // );
}

/**
 * Scalar-matrix multiplication.
 */
template <typename T>
Mat4<T> operator*(T s, const Mat4<T>& m)
{
    const T* a = m.data();
    Mat4<T> result;
    T* o = result.data();
    for (unsigned int i = 0; i < 16; ++i) {
        o[i] = s * a[i];
    }
    return result;
}

/**
 * Matrix-scalar multiplication.
 */
template <typename T>
Mat4<T> operator*(const Mat4<T>& m, T s)
{
    const T* a = m.data();
    Mat4<T> result;
    T* o = result.data();
    for (unsigned int i = 0; i < 16; ++i) {
        o[i] = a[i] * s;
    }
    return result;
}

/**
 * Returns the 3x3 top-left part of the matrix.
 */
template <typename T>
Mat3<T> topleft(const Mat4<T>& m)
{
    const T* a = m.data();
    Mat3<T> result;
    T* o = result.data();

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

/**
 * Returns the transposed inverse of the 3x3 top-left part of the matrix. Used
 * for normal transform calculations.
 */
template <typename T>
Mat3<T> normal_matrix(const Mat4<T>& m)
{
    return transposed_inverse(topleft(m));
}

/**
 * Returns the transpose of the matrix.
 */
template <typename T>
Mat4<T> transpose(const Mat4<T>& m)
{
    Mat4<T> result;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result(j, i) = m(i, j);
        }
    }

    return result;
}

};

#endif
