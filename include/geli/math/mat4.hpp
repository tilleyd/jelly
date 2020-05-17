#ifndef _GELI_MATH_MAT4_HPP_
#define _GELI_MATH_MAT4_HPP_

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
     *     The field of view of the projection.
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
    Mat4(T m[16]) : _data(m) {}

    /**
     * Returns a pointer to the matrix.
     *
     * \note The array is in column-major form.
     */
    T* data() { return _data; }

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
    float t = n * tanf((fov * M_PI / 180.0f) * 0.5f);
    float b = -t;
    float r = t * ratio;
    float l = -r;
    return Mat4<T>({
         2.0f*n/(r-l),   0.0f,            0.0f,           0.0f,
         0.0f,           2.0f*n/(t-b),    0.0f,           0.0f,
         0.0f,           0.0f,           -(f+n)/(f-n),   -1.0f,
        -n*(r+l)/(r-l), -n*(t+b)/(t-b),   2.0f*f*n/(n-f), 0.0f
    });
}

template <typename T>
Mat4<T> Mat4<T>::orthographic(float l, float r, float b, float t, float n, float f)
{
    return Mat4<T>({
         2.0f/(r-l),   0.0f,         0.0f,        0.0f,
         0.0f,         2.0f/(t-b),   0.0f,        0.0f,
         0.0f,         0.0f,        -2.0f/(f-n),  0.0f,
        -(r+l)/(r-l), -(t+b)/(t-b), -(f+n)/(f-n), 1.0f
    });
}

};

#endif
