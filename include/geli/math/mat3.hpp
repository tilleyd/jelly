#ifndef _GELI_MATH_MAT3_HPP_
#define _GELI_MATH_MAT3_HPP_

#include <cmath>

#include <geli/math/vec3.hpp>

namespace geli
{

template <typename T>
class Mat3
{

public:

    /**
     * Creates a zero Mat3.
     */
    Mat3() : _data{} {}

    /**
     * Creates a diagonal Mat3 with all diagonals set to the provided value.
     */
    Mat3(T d) : _data{d, 0, 0,
                      0, d, 0,
                      0, 0, d} {}

    /**
     * Creates a Mat3 from the given array.
     *
     * \note The array must be in column-major form.
     */
    Mat3(T m[9])
    {
        for (unsigned int i = 0; i < 9; ++i) _data[i] = m[i];
    }

    /**
     * Returns a pointer to the matrix.
     *
     * \note The array is in column-major form.
     */
    T* data() { return _data; }

    T& operator()(unsigned int r, unsigned int c) { return _data[3*c+r]; }
    T operator()(unsigned int r, unsigned int c) const { return _data[3*c+r]; }

    T& operator[](unsigned int i) { return _data[i]; }
    T operator[](unsigned int i) const { return _data[i]; }

    /**
     * Returns a pointer to the matrix.
     *
     * \note the array is in column-major form.
     */
    const T* data() const { return _data; }

private:

    T _data[9];

};

typedef Mat3<double> Mat3d;
typedef Mat3<int> Mat3i;
typedef Mat3<float> Mat3f;

/**
 * Matrix-matrix multiplication.
 */
template <typename T>
Mat3<T> operator*(const Mat3<T>& m1, const Mat3<T>& m2)
{
    const T* a = m1.data();
    const T* b = m2.data();
    Mat3<T> result;
    T* o = result.data();

    T a00 = a[0];
    T a10 = a[1];
    T a20 = a[2];
    T a01 = a[3];
    T a11 = a[4];
    T a21 = a[5];
    T a02 = a[6];
    T a12 = a[7];
    T a22 = a[8];
    for (unsigned int col = 0; col < 3; ++col) {
        unsigned int i1 = col*3;
        unsigned int i2 = i1+1;
        unsigned int i3 = i1+2;
        T b0 = b[i1];
        T b1 = b[i2];
        T b2 = b[i3];
        o[i1] = a00 * b0 + a01 * b1 + a02 * b2;
        o[i2] = a10 * b0 + a11 * b1 + a12 * b2;
        o[i3] = a20 * b0 + a21 * b1 + a22 * b2;
    }

    return result;
}

/**
 * Vector-matrix multiplication.
 */
template <typename T>
Vec3<T> operator*(const Mat3<T>& m, const Vec3<T>& v)
{
    const T* a = m.data();
    const T* b = v.data();

    T v0 = v.x();
    T v1 = v.y();
    T v2 = v.z();

    return Vec3<T>(
        m[0]*v0 + m[4]*v1 + m[8]*v2,
        m[1]*v0 + m[5]*v1 + m[9]*v2,
        m[2]*v0 + m[6]*v1 + m[10]*v2
    );
}

/**
 * Scalar-matrix multiplication.
 */
template <typename T>
Mat3<T> operator*(T s, const Mat3<T>& m)
{
    const T* a = m.data();
    Mat3<T> result;
    T* o = result.data();
    for (unsigned int i = 0; i < 9; ++i) {
        o[i] = s * a[i];
    }
    return result;
}

/**
 * Matrix-scalar multiplication.
 */
template <typename T>
Mat3<T> operator*(const Mat3<T>& m, T s)
{
    const T* a = m.data();
    Mat3<T> result;
    T* o = result.data();
    for (unsigned int i = 0; i < 9; ++i) {
        o[i] = a[i] * s;
    }
    return result;
}

/**
 * Returns the determinant of the matrix.
 */
template <typename T>
float determinant(const Mat3<T>& m)
{
    float d1 = m(0, 0) * (m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1));
    float d2 = m(0, 1) * (m(1, 0) * m(2, 2) - m(1, 2) * m(2, 0));
    float d3 = m(0, 2) * (m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0));
    return d1 - d2 + d3;
}

/**
 * Returns the transpose of the matrix.
 */
template <typename T>
Mat3<T> transpose(const Mat3<T>& m)
{
    Mat3<T> result;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result(j, i) = m(i, j);
        }
    }

    return result;
}

/**
 * Returns the transposed inverse of the matrix.
 *
 * \note The matrix is assumed to be invertible.
 */
template <typename T>
Mat3<T> transposed_inverse(const Mat3<T>& m)
{
    Mat3<T> result;
    T* o = result.data();

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

};

#endif
