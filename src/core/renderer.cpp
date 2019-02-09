#include <geli/core/renderer.h>

#include <geli/core/shader.h>
#include <cmath>

using namespace geli::core;

Renderer::Renderer(Shader& shader) :
    _shader(shader),
    _mMatrix(1.0f)
{
    initSquare();
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

void Renderer::renderCircle() const
{
    _shader.setMMatrix(_mMatrix);
    _circle->render();
}

void Renderer::initSquare()
{
    const float squareVertices[] = {
        0.5f, -0.5f, 0.0f, // half to get unit width and height
        0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f
    };
    _square.reset(new Model(squareVertices, 4, GL_TRIANGLE_STRIP));
}

void Renderer::initCircle()
{
    constexpr unsigned int CIRCLE_RESOLUTION = 16;
    constexpr unsigned int CIRCLE_BUFFER_SIZE = 3 * CIRCLE_RESOLUTION;
    float circleVertices[CIRCLE_BUFFER_SIZE];
    float angleStep = M_PI * 2.0 / CIRCLE_RESOLUTION;
    float angle = 0.0;

    for (unsigned int i = 0; i < CIRCLE_BUFFER_SIZE; i += 3) {
        float x = cos(angle) * 0.5; // half to get unit width and height
        float y = sin(angle) * 0.5;
        circleVertices[i] = x;
        circleVertices[i+1] = y;
        circleVertices[i+2] = 0.0f;
        angle += angleStep;
    }

    _circle.reset(new Model(circleVertices,
                            CIRCLE_RESOLUTION,
                            GL_TRIANGLE_FAN));
}
