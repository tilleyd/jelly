#include <geli/mesh.hpp>

using namespace geli;

Mesh::Mesh(const float vertices[],
           const float normals[],
           const float uvs[],
           const unsigned int indices[],
           unsigned int n,
           unsigned int mode) :
    _numVertices(n),
    _vbo(0),
    _vao(0),
    _renderMode(mode)
{
    // combine the buffers into a single buffer and store in the format
    // {x y z nx ny nz u v ...}
    float* buffer = new float[n * 8];
    for (unsigned int i = 0; i < n; ++i)
    {
        buffer[i*8+0] = vertices[i*3+0];
        buffer[i*8+1] = vertices[i*3+1];
        buffer[i*8+2] = vertices[i*3+2];
        buffer[i*8+3] = normals[i*3+0];
        buffer[i*8+4] = normals[i*3+1];
        buffer[i*8+5] = normals[i*3+2];
        buffer[i*8+6] = uvs[i*2+0];
        buffer[i*8+7] = uvs[i*2+1];
    }

    // create the vertex attribute object
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    // create the vertex buffer object and assign it
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, n * sizeof(float) * 8, buffer, GL_STATIC_DRAW);

    // configure vertex attributes
    // vertices attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normals attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 & sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coordinates attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    delete [] buffer;
}

Mesh::~Mesh()
{
    if (_vao) {
        glDeleteVertexArrays(1, &_vao);
    }
    if (_vbo) {
        glDeleteBuffers(1, &_vbo);
    }
}
