#include <jelly/mesh.hpp>


namespace jelly {


Mesh* Mesh::square_mesh(float ext) {
    std::vector<Vec3> vertices = {
        Vec3(-ext, -ext, 0.0f),
        Vec3( ext, -ext, 0.0f),
        Vec3( ext,  ext, 0.0f),
        Vec3(-ext,  ext, 0.0f)
    };
    std::vector<Vec3> normals = {
        Vec3(0.0f, 0.0f, 1.0f),
        Vec3(0.0f, 0.0f, 1.0f),
        Vec3(0.0f, 0.0f, 1.0f),
        Vec3(0.0f, 0.0f, 1.0f)
    };
    std::vector<Vec2> uvs = {
        Vec2(0.0f, 0.0f),
        Vec2(1.0f, 0.0f),
        Vec2(1.0f, 1.0f),
        Vec2(0.0f, 1.0f)
    };
    std::vector<unsigned int> indices = {0, 1, 2, 0, 2, 3};

    return new Mesh(vertices, normals, uvs, indices);
}


Mesh* Mesh::cube_mesh(float ext) {
    std::vector<Vec3> vertices = {
        Vec3(-ext,  ext,  ext), Vec3(-ext, -ext,  ext), Vec3( ext, -ext,  ext), Vec3( ext,  ext,  ext),
        Vec3(-ext,  ext, -ext), Vec3(-ext, -ext, -ext), Vec3( ext, -ext, -ext), Vec3( ext,  ext, -ext),
        Vec3(-ext,  ext,  ext), Vec3( ext,  ext,  ext), Vec3(-ext,  ext, -ext), Vec3( ext,  ext, -ext),
        Vec3(-ext, -ext,  ext), Vec3( ext, -ext,  ext), Vec3(-ext, -ext, -ext), Vec3( ext, -ext, -ext),
        Vec3(-ext,  ext,  ext), Vec3(-ext, -ext,  ext), Vec3(-ext,  ext, -ext), Vec3(-ext, -ext, -ext),
        Vec3( ext,  ext,  ext), Vec3( ext, -ext,  ext), Vec3( ext,  ext, -ext), Vec3( ext, -ext, -ext)
    };
    std::vector<Vec3> normals = {
        Vec3( 0.0f,  0.0f,  1.0f), Vec3( 0.0f,  0.0f,  1.0f), Vec3( 0.0f,  0.0f,  1.0f), Vec3( 0.0f,  0.0f,  1.0f),
        Vec3( 0.0f,  0.0f, -1.0f), Vec3( 0.0f,  0.0f, -1.0f), Vec3( 0.0f,  0.0f, -1.0f), Vec3( 0.0f,  0.0f, -1.0f),
        Vec3( 0.0f,  1.0f,  0.0f), Vec3( 0.0f,  1.0f,  0.0f), Vec3( 0.0f,  1.0f,  0.0f), Vec3( 0.0f,  1.0f,  0.0f),
        Vec3( 0.0f, -1.0f,  0.0f), Vec3( 0.0f, -1.0f,  0.0f), Vec3( 0.0f, -1.0f,  0.0f), Vec3( 0.0f, -1.0f,  0.0f),
        Vec3(-1.0f,  0.0f,  0.0f), Vec3(-1.0f,  0.0f,  0.0f), Vec3(-1.0f,  0.0f,  0.0f), Vec3(-1.0f,  0.0f,  0.0f),
        Vec3( 1.0f,  0.0f,  0.0f), Vec3( 1.0f,  0.0f,  0.0f), Vec3( 1.0f,  0.0f,  0.0f), Vec3( 1.0f,  0.0f,  0.0f)
    };
    std::vector<Vec2> uvs = {
        Vec2(0.0f, 1.0f), Vec2(0.0f, 0.0f), Vec2(1.0f, 0.0f), Vec2(1.0f, 1.0f),
        Vec2(0.0f, 1.0f), Vec2(0.0f, 0.0f), Vec2(1.0f, 0.0f), Vec2(1.0f, 1.0f),
        Vec2(0.0f, 1.0f), Vec2(1.0f, 1.0f), Vec2(0.0f, 0.0f), Vec2(1.0f, 0.0f),
        Vec2(0.0f, 1.0f), Vec2(1.0f, 1.0f), Vec2(0.0f, 0.0f), Vec2(1.0f, 0.0f),
        Vec2(1.0f, 1.0f), Vec2(0.0f, 1.0f), Vec2(1.0f, 0.0f), Vec2(0.0f, 0.0f),
        Vec2(1.0f, 1.0f), Vec2(0.0f, 1.0f), Vec2(1.0f, 0.0f), Vec2(0.0f, 0.0f)
    };
    std::vector<unsigned int> indices = {
        0, 1, 2, 0, 2, 3,
        7, 6, 4, 6, 5, 4,
        8, 9, 10, 11, 10, 9,
        14, 13, 12, 13, 14, 15,
        18, 17, 16, 17, 18, 19,
        20, 21, 22, 23, 22, 21
    };
    return new Mesh(vertices, normals, uvs, indices);
}

Mesh* Mesh::sphere_mesh(unsigned int latr, unsigned int lngr, float rad)
{
    unsigned int numVertex = (lngr+1)*(latr+1);
    unsigned int numIndex = 6*lngr*latr;

    std::vector<Vec3> vertices;
    std::vector<Vec3> normals;
    std::vector<Vec2> uvs;
    std::vector<unsigned int> indices;

    // create vertex data
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

            vertices.emplace_back(rad * x, rad * y, rad * z);
            normals.emplace_back(x, y, z);
            uvs.emplace_back(u, v);
        }
    }

    // create element triangle data
    for (int lng = 0; lng < lngr; ++lng) {
        for (int lat = 0; lat < latr; ++lat) {
            unsigned int first = lng * (latr + 1) + lat;
            unsigned int second = first + latr + 1;

            indices.emplace_back(first + 1);
            indices.emplace_back(second);
            indices.emplace_back(first);

            indices.emplace_back(first + 1);
            indices.emplace_back(second + 1);
            indices.emplace_back(second);
        }
    }

    return new Mesh(vertices, normals, uvs, indices);
}


Mesh::Mesh(
    const std::vector<Vec3>& vertices,
    const std::vector<Vec3>& normals,
    const std::vector<Vec2>& uvs,
    const std::vector<unsigned int> indices,
    unsigned int mode
) :
    _numIndices(indices.size()),
    _vbo(0),
    _ebo(0),
    _vao(0),
    _renderMode(mode)
{
    // Combine the vertex info into a single buffer and store in the format
    // {x y z nx ny nz u v ...}
    float* buffer = new float[8 * vertices.size()];

    for (unsigned int i = 0; i < vertices.size(); ++i)
    {
        const Vec3& vertex = vertices[i];
        const Vec3& normal = normals[i];
        const Vec2& uv = uvs[i];
        buffer[i*8+0] = vertex.x();
        buffer[i*8+1] = vertex.y();
        buffer[i*8+2] = vertex.z();
        buffer[i*8+3] = normal.x();
        buffer[i*8+4] = normal.y();
        buffer[i*8+5] = normal.z();
        buffer[i*8+6] = uv.x();
        buffer[i*8+7] = uv.y();
    }

    // Create the vertex attribute object
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    // Create the vertex buffer object and assign it
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(float) * 8,
        buffer,
        GL_STATIC_DRAW
    );

    // Create the element buffer object and assign it
    glGenBuffers(1, &_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        _numIndices * sizeof(unsigned int),
        indices.data(),
        GL_STATIC_DRAW
    );

    // Configure vertex attributes
    // Vertices attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Normals attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Texture coordinates attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    delete [] buffer;
}


Mesh::~Mesh() {
    if (_vao) {
        glDeleteVertexArrays(1, &_vao);
    }
    if (_vbo) {
        glDeleteBuffers(1, &_vbo);
    }
    if (_ebo) {
        glDeleteBuffers(1, &_ebo);
    }
}


void Mesh::_render() const {
    if (_vao) {
        glBindVertexArray(_vao);
        glDrawElements(_renderMode, _numIndices, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}


}
