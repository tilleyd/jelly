#ifndef _JELLY_MATH_MAT3_HPP_
#define _JELLY_MATH_MAT3_HPP_

#include <jelly/math/vec3.hpp>

namespace jelly {

class Mat3 {

public:

    /**
     * Creates a zero Mat3.
     */
    Mat3() : _data{} {}

    /**
     * Creates a diagonal Mat3 with all diagonals set to the provided value.
     */
    Mat3(float d) : _data{d, 0, 0,
                      0, d, 0,
                      0, 0, d} {}

    /**
     * Creates a Mat3 from the given array.
     *
     * \note The array must be in column-major form.
     */
    Mat3(float m[9])
    {
        for (unsigned int i = 0; i < 9; ++i) _data[i] = m[i];
    }

    /**
     * Returns a pointer to the matrix.
     *
     * \note The array is in column-major form.
     */
    float* data() { return _data; }

    float& operator()(unsigned int r, unsigned int c) { return _data[3*c+r]; }
    float operator()(unsigned int r, unsigned int c) const { return _data[3*c+r]; }

    float& operator[](unsigned int i) { return _data[i]; }
    float operator[](unsigned int i) const { return _data[i]; }

    /**
     * Returns a pointer to the matrix.
     *
     * \note the array is in column-major form.
     */
    const float* data() const { return _data; }

private:

    float _data[9];

};


/**
 * Matrix-matrix multiplication.
 */
Mat3 operator*(const Mat3& m1, const Mat3& m2);

/**
 * Vector-matrix multiplication.
 */
Vec3 operator*(const Mat3& m, const Vec3& v);

/**
 * Scalar-matrix multiplication.
 */
Mat3 operator*(float s, const Mat3& m);

/**
 * Matrix-scalar multiplication.
 */
Mat3 operator*(const Mat3& m, float s);

/**
 * Returns the determinant of the matrix.
 */
float determinant(const Mat3& m);

/**
 * Returns the transpose of the matrix.
 */
Mat3 transpose(const Mat3& m);

/**
 * Returns the transposed inverse of the matrix.
 *
 * \note The matrix is assumed to be invertible.
 */
Mat3 transposed_inverse(const Mat3& m);

}

#endif
