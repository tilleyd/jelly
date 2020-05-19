#ifndef _GELI_MATH_MAT4_HPP_
#define _GELI_MATH_MAT4_HPP_

#include <cmath>

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
     * Returns a pointer to the matrix.
     *
     * \note The array is in column-major form.
     */
    T* data() { return _data; }

    T& operator()(unsigned int r, unsigned int c) { return _data[4*c+r]; }
    T operator()(unsigned int r, unsigned int c) const { return _data[4*c+r]; }

    /**
     * Returns a pointer to the matrix.
     *
     * \note the array is in column-major form.
     */
    const T* data() const { return _data; }

    /**
     * Matrix-matrix multiplication.
     */
    Mat4<T> operator*(const Mat4<T>&) const;

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

template <typename T>
Mat4<T> Mat4<T>::operator*(const Mat4<T>& m) const
{
    // cache-coherent multiplication as done by glm
    const T* a = _data;
    const T* b = m._data;
    Mat4<T> result;
    T* o = result._data;

    T a00 = a[0];
    T a01 = a[1];
    T a02 = a[2];
    T a03 = a[3];
    T a10 = a[4];
    T a11 = a[5];
    T a12 = a[6];
    T a13 = a[7];
    T a20 = a[8];
    T a21 = a[9];
    T a22 = a[10];
    T a23 = a[11];
    T a30 = a[12];
    T a31 = a[13];
    T a32 = a[14];
    T a33 = a[15];

    T b0 = b[0];
    T b1 = b[1];
    T b2 = b[2];
    T b3 = b[3];
    o[0] = b0 * a00 + b1 * a10 + b2 * a20 + b3 * a30;
    o[1] = b0 * a01 + b1 * a11 + b2 * a21 + b3 * a31;
    o[2] = b0 * a02 + b1 * a12 + b2 * a22 + b3 * a32;
    o[3] = b0 * a03 + b1 * a13 + b2 * a23 + b3 * a33;

    b0 = b[4];
    b1 = b[5];
    b2 = b[6];
    b3 = b[7];
    o[4] = b0 * a00 + b1 * a10 + b2 * a20 + b3 * a30;
    o[5] = b0 * a01 + b1 * a11 + b2 * a21 + b3 * a31;
    o[6] = b0 * a02 + b1 * a12 + b2 * a22 + b3 * a32;
    o[7] = b0 * a03 + b1 * a13 + b2 * a23 + b3 * a33;

    b0 = b[8];
    b1 = b[9];
    b2 = b[10];
    b3 = b[11];
    o[8] = b0 * a00 + b1 * a10 + b2 * a20 + b3 * a30;
    o[9] = b0 * a01 + b1 * a11 + b2 * a21 + b3 * a31;
    o[10] = b0 * a02 + b1 * a12 + b2 * a22 + b3 * a32;
    o[11] = b0 * a03 + b1 * a13 + b2 * a23 + b3 * a33;

    b0 = b[12];
    b1 = b[13];
    b2 = b[14];
    b3 = b[15];
    o[12] = b0 * a00 + b1 * a10 + b2 * a20 + b3 * a30;
    o[13] = b0 * a01 + b1 * a11 + b2 * a21 + b3 * a31;
    o[14] = b0 * a02 + b1 * a12 + b2 * a22 + b3 * a32;
    o[15] = b0 * a03 + b1 * a13 + b2 * a23 + b3 * a33;

    return result;
}

};

#endif
