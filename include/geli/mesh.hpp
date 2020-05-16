#ifndef _GELI_MESH_HPP_
#define _GELI_MESH_HPP_

#include <GL/glew.h>

namespace geli
{

/**
 * Represents a renderable geometry mesh containing vertex, normal and uv-coord
 * buffers with an index array.
 */
class Mesh
{

public:

    Mesh() = delete;
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    /**
     * Creates a mesh from the given buffer arrays.
     *
     * \param vertices
     *     The array of vertices. The vertex array must be in the format
     *     { x1, y1, z1 ... xn, yn, zn } and have size 3*n.
     * \param normals
     *     The array of vertex normals. The normals array must be in the
     *     format { x1, y1, z1 ... xn, yn, zn } and have size 3*n.
     * \param uvs
     *     The array of UV/texture coordinates. The UV array must be in the
     *     format { u1, v1 ... un, vn } and have size 2*n.
     * \param indices
     *     The index array used for rendering primitives. Must have the
     *     appropriate size for the mode specified.
     * \param n
     *     The number of vertices in the mesh.
     * \param mode
     *     The OpenGL rendering mode used to render the vertices, e.g.
     *     GL_POINTS, GL_LINE_STRIP, GL_TRIANGLES, etc.
     */
    Mesh(const float vertices[],
            const float normals[],
            const float uvs[],
            unsigned int n,
            const unsigned int indices[],
            unsigned int ni,
            unsigned int mode = GL_TRIANGLES);

    /**
     * Clears resources used by the mesh.
     */
    ~Mesh();

    /**
     * Renders the current mesh using the active shader.
     */
    void render() const;

    /**
     * Returns a handle to the OpenGL vertex buffer object.
     */
    unsigned int get_vbo() const
    {
        return _vbo;
    }

    /**
     * Returns a handle to the OpenGL element buffer object.
     */
    unsigned int get_ebo() const
    {
        return _ebo;
    }

    /**
     * Returns a handle to the OpenGL vertex attribute object.
     */
    unsigned int get_vao() const
    {
        return _vao;
    }

    /**
     * Returns the render mode of the mesh.
     */
    unsigned int get_render_mode() const
    {
        return _renderMode;
    }

private:

    unsigned int _numVertices;
    unsigned int _numIndices;
    unsigned int _vbo;
    unsigned int _ebo;
    unsigned int _vao;
    unsigned int _renderMode;

};

};

#endif
