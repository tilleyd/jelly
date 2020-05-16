/**
 * Contains definitions and initialization of all predefined meshes.
 */

#include <geli/mesh.hpp>

using namespace geli;

std::shared_ptr<Mesh> Mesh::_squareMesh = nullptr;
std::shared_ptr<Mesh> Mesh::_cubeMesh = nullptr;

std::shared_ptr<Mesh> Mesh::square_mesh()
{
    if (!_squareMesh) {
        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
        };
        float normals[] = {
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f
        };
        float uvs[] = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f
        };
        unsigned int indices[] = {0, 1, 2, 0, 2, 3};
        _squareMesh = std::make_shared<Mesh>(vertices, normals, uvs, 4, indices, 6);
    }

    return _squareMesh;
}

std::shared_ptr<Mesh> Mesh::cube_mesh()
{
    if (!_cubeMesh) {
        float vertices[] = {
            -0.5f,  0.5f,  0.5f, -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,
            -0.5f,  0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f,
             0.5f,  0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f
        };
        float normals[] = {
             0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
             0.0f,  0.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f, -1.0f,
             0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
             0.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,
            -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
             1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f
        };
        float uvs[] = {
            0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f
        };
        unsigned int indices[] = {
            0, 1, 2, 0, 2, 3,
            7, 6, 4, 6, 5, 4,
            8, 9, 10, 11, 10, 9,
            14, 13, 12, 13, 14, 15,
            18, 17, 16, 17, 18, 19,
            20, 21, 22, 23, 22, 21
        };
        _cubeMesh = std::make_shared<Mesh>(vertices, normals, uvs, 24, indices, 36);
    }

    return _cubeMesh;
}
