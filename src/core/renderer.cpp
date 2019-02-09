#include <geli/core/renderer.h>

#include <geli/core/shader.h>

using namespace geli::core;

Renderer::Renderer(Shader& shader) :
    _shader(shader),
    _mMatrix(1.0f)
{
    initSquare();
    initTriangle();
    initCircle();
}

void Renderer::resetTransform()
{
    _mMatrix = glm::mat4(1.0f);
}

void Renderer::translateTransform(float x, float y, float z)
{
    _mMatrix = glm::translate(_mMatrix, glm::vec3(x, y, z));
}

void Renderer::scaleTransform(float x, float y, float z)
{
    _mMatrix = glm::scale(_mMatrix, glm::vec3(x, y, z));
}

void Renderer::renderSquare() const
{
    _shader.setMMatrix(_mMatrix);
    _square->render();
}

void Renderer::initSquare()
{
    const float squareVertices[] = {
        1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f
    };
    _square.reset(new Model(squareVertices, 4, GL_TRIANGLE_STRIP));
}

void Renderer::initTriangle()
{}

void Renderer::initCircle()
{}
