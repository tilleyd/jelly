/**
 * Contains definitions and initialization of all predefined meshes.
 */

#include <geli/mesh.hpp>

#include <cmath>

using namespace geli;

std::shared_ptr<Mesh> Mesh::create_square_mesh(float ext)
{
    float vertices[] = {
        -ext, -ext, 0.0f,
         ext, -ext, 0.0f,
         ext,  ext, 0.0f,
        -ext,  ext, 0.0f
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

    return std::make_shared<Mesh>(vertices, normals, uvs, 4, indices, 6);
}

std::shared_ptr<Mesh> Mesh::create_cube_mesh(float ext)
{
    float vertices[] = {
        -ext,  ext,  ext, -ext, -ext,  ext,  ext, -ext,  ext,  ext,  ext,  ext,
        -ext,  ext, -ext, -ext, -ext, -ext,  ext, -ext, -ext,  ext,  ext, -ext,
        -ext,  ext,  ext,  ext,  ext,  ext, -ext,  ext, -ext,  ext,  ext, -ext,
        -ext, -ext,  ext,  ext, -ext,  ext, -ext, -ext, -ext,  ext, -ext, -ext,
        -ext,  ext,  ext, -ext, -ext,  ext, -ext,  ext, -ext, -ext, -ext, -ext,
         ext,  ext,  ext,  ext, -ext,  ext,  ext,  ext, -ext,  ext, -ext, -ext
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
    return std::make_shared<Mesh>(vertices, normals, uvs, 24, indices, 36);
}

std::shared_ptr<Mesh> Mesh::create_sphere_mesh(unsigned int latr, unsigned int lngr, float rad)
{
    unsigned int numVertex = (lngr+1)*(latr+1);
    unsigned int numIndex = 6*lngr*latr;

    float* vertices = new float[3*numVertex];
    float* normals = new float[3*numVertex];
    float* uvs = new float[2*numVertex];
    unsigned int* indices = new unsigned int[numIndex];


    // create vertex data
    unsigned int vi = 0, ni = 0, uvi = 0;
    for (int lng = 0; lng <= lngr; ++lng) {
        float theta = lng * M_PI / lngr;
        float sinTheta = sinf(theta);
        float cosTheta = cosf(theta);

        float y = cosTheta;
        float v = 1.0f - (lng / (float)lngr);

        for (int lat = 0; lat <= latr; ++lat) {
            float phi = lat * 2.0f * M_PI / latr;
            float sinPhi = sinf(phi);
            float cosPhi = cosf(phi);

            // create vertex data
            float x = cosPhi * sinTheta;
            float z = sinPhi * sinTheta;
            float u = 1.0f - (lat / (float)latr);

            vertices[vi++] = x * rad;
            vertices[vi++] = y * rad;
            vertices[vi++] = z * rad;
            normals[ni++] = x;
            normals[ni++] = y;
            normals[ni++] = z;
            uvs[uvi++] = u;
            uvs[uvi++] = v;
        }
    }

    // create element triangle data
    unsigned int ii = 0;
    for (int lng = 0; lng < lngr; ++lng) {
        for (int lat = 0; lat < latr; ++lat) {
            unsigned int first = lng * (latr + 1) + lat;
            unsigned int second = first + latr + 1;

            indices[ii++] = first + 1;
            indices[ii++] = second;
            indices[ii++] = first;

            indices[ii++] = first + 1;
            indices[ii++] = second + 1;
            indices[ii++] = second;
        }
    }

    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(vertices, normals, uvs, numVertex, indices, numIndex);

    delete [] vertices;
    delete [] normals;
    delete [] uvs;
    delete [] indices;

    return mesh;
}
