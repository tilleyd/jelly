#include <geli/core/model.h>

using geli::core::Model;

Model::Model(const float vert[], unsigned int n, unsigned int mode) :
    _numVertices(n),
    _vbo(0),
    _vao(0),
    _renderMode(mode)
{
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    // create VBO
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, n * sizeof(float) * 3, vert, GL_STATIC_DRAW);

    // configure vertex array attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

Model::~Model()
{
    if (_vao) {
        glDeleteVertexArrays(1, &_vao);
    }
    if (_vbo) {
        glDeleteBuffers(1, &_vbo);
    }
}

void Model::render() const
{
    glBindVertexArray(_vao);
    glDrawArrays(_renderMode, 0, _numVertices);
    glBindVertexArray(0);
}
