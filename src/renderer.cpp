#include <geli/renderer.h>

using namespace geli;

Renderer::Renderer()
{
    initSquare();
    initTriangle();
    initCircle();
}

void Renderer::renderSquare() const
{
    _square->render();
}

void Renderer::initSquare()
{
    const float squareVertices[] = {
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };
    _square.reset(new Model(squareVertices, 3));
}

void Renderer::initTriangle()
{}

void Renderer::initCircle()
{}
