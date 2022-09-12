#ifndef _JELLY_MESH_HPP_
#define _JELLY_MESH_HPP_

#include <vector>

#include <GL/glew.h>

#include <jelly/math/vec2.hpp>
#include <jelly/math/vec3.hpp>

namespace jelly {

/**
 * Represents a renderable geometry mesh containing vertex, normal and uv-coord
 * buffers with an index array.
 */
class Mesh {

public:

    Mesh() = delete;
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    /**
     * Creates a flat square mesh in the xy-plane with an origin at the center.
     *
     * \param extent
     *     The square's extent from the centre in each direction.
     */
    static Mesh* square_mesh(float extent=1.0f);

    /**
     * Creates a flat square mesh in the xy-plane with an origin at the
     * bottom-left corner. Quad meshes are easier to manipulate for drawing
     * at specified locations compared to square meshes.
     *
     * \param size
     *     The quad's size.
     */
    static Mesh* quad_mesh(float size=1.0f);

    /**
     * Creates a cube mesh.
     *
     * \param extent
     *     The cube's extent from the centre in each direction
     */
    static Mesh* cube_mesh(float extent=1.0f);

    /**
     * Creates a sphere mesh.
     *
     * \param latRes
     *     The number of vertices to create along the latitudinal (horizontal).
     * \param lngRes
     *     The number of vertices to create along the longitudinal (vertical).
     * \param radius
     *     The sphere's radius.
     */
    static Mesh* sphere_mesh(unsigned int latRes=16, unsigned int lngRes=16, float radius=1.0f);

    /**
     * Creates a mesh from the given buffer arrays.
     *
     * \param vertices
     *     The vector of vertices.
     * \param normals
     *     The vector of vertex normals, equal in length to `vertices`.
     * \param uvs
     *     The vector of UV/texture coordinates, equal in length to `vertices`.
     * \param indices
     *     The index array used for rendering primitives. Must have the
     *     appropriate size for the primitive mode specified.
     * \param mode
     *     The OpenGL primitive mode used to render the vertices, e.g.
     *     GL_POINTS, GL_LINE_STRIP, GL_TRIANGLES, etc.
     */
    Mesh(
        const std::vector<Vec3>& vertices,
        const std::vector<Vec3>& normals,
        const std::vector<Vec2>& uvs,
        const std::vector<unsigned int> indices,
        unsigned int mode = GL_TRIANGLES
    );

    /**
     * Clears resources used by the mesh.
     */
    ~Mesh();

    /**
     * Returns a handle to the OpenGL vertex buffer object.
     */
    unsigned int get_vbo_handle() const
    {
        return _vbo;
    }

    /**
     * Returns a handle to the OpenGL element buffer object.
     */
    unsigned int get_ebo_handle() const
    {
        return _ebo;
    }

    /**
     * Returns a handle to the OpenGL vertex attribute object.
     */
    unsigned int get_vao_handle() const
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

    friend class Context;

    void _render() const;

    unsigned int _numIndices;
    unsigned int _vbo;
    unsigned int _ebo;
    unsigned int _vao;
    unsigned int _renderMode;

};

}

#endif
