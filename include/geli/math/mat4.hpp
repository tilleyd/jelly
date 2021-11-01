#ifndef _GELI_MATH_MAT4_HPP_
#define _GELI_MATH_MAT4_HPP_

#include <geli/math/vec4.hpp>
#include <geli/math/mat3.hpp>

namespace geli
{

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
    static Mat4 perspective(float fov, float ratio, float near, float far);

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
    static Mat4 orthographic(float l, float r, float b, float t, float n, float f);

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
    static Mat4 look_at(const Vec3& origin, const Vec3& target, const Vec3& up);

    /**
     * Creates a translation matrix.
     *
     * \param t
     *     The translation vector.
     */
    static Mat4 translation(const Vec3& t);

    /**
     * Creates an x rotation matrix.
     *
     * \param a
     *     The x rotation angle in radians.
     */
    static Mat4 x_rotation(float a);

    /**
     * Creates a y rotation matrix.
     *
     * \param a
     *     The y rotation angle in radians.
     */
    static Mat4 y_rotation(float a);

    /**
     * Creates a z rotation matrix.
     *
     * \param a
     *     The z rotation angle in radians.
     */
    static Mat4 z_rotation(float a);

    /**
     * Creates a scaling matrix.
     *
     * \param s
     *     The scale to apply per axis.
     */
    static Mat4 scale(Vec3 s);

    /**
     * Creates a zero Mat4.
     */
    Mat4() : _data{} {}

    /**
     * Creates a diagonal Mat4 with all diagonals set to the provided value.
     */
    Mat4(float d) : _data{d, 0, 0, 0,
                      0, d, 0, 0,
                      0, 0, d, 0,
                      0, 0, 0, d} {}

    /**
     * Creates a Mat4 from the given array.
     *
     * \note The array must be in column-major form.
     */
    Mat4(float m[16])
    {
        for (unsigned int i = 0; i < 16; ++i) _data[i] = m[i];
    }

    /**
     * Creates a Mat4 containing the Mat3 as the top-left part of the matrix
     * and w at position (3, 3).
     */
    Mat4(const Mat3& m, float w = 1.0) : _data{m[0], m[1], m[2], 0,
                                              m[3], m[4], m[5], 0,
                                              m[6], m[7], m[8], 0,
                                              0,    0,    0,    w} {}

    /**
     * Returns a pointer to the matrix.
     *
     * \note The array is in column-major form.
     */
    float* data() { return _data; }

    float& operator()(unsigned int r, unsigned int c) { return _data[4*c+r]; }
    float operator()(unsigned int r, unsigned int c) const { return _data[4*c+r]; }

    float& operator[](unsigned int i) { return _data[i]; }
    float operator[](unsigned int i) const { return _data[i]; }

    /**
     * Returns a pointer to the matrix.
     *
     * \note the array is in column-major form.
     */
    const float* data() const { return _data; }

private:

    float _data[16];

};

/**
 * Matrix multiplication.
 */
Mat4 operator*(const Mat4& m1, const Mat4& m2);

/**
 * Vector-matrix multiplication.
 */
Vec4 operator*(const Mat4& m, const Vec4& v);

/**
 * Scalar-matrix multiplication.
 */
Mat4 operator*(float s, const Mat4& m);

/**
 * Matrix-scalar multiplication.
 */
Mat4 operator*(const Mat4& m, float s);

/**
 * Returns the 3x3 top-left part of the matrix.
 */
Mat3 topleft(const Mat4& m);

/**
 * Returns the transposed inverse of the 3x3 top-left part of the matrix. Used
 * for normal transform calculations.
 */
Mat3 normal_matrix(const Mat4& m);

/**
 * Returns the transpose of the matrix.
 */
Mat4 transpose(const Mat4& m);

};

#endif
