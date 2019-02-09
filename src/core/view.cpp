#include <geli/core/view.h>

#include <geli/core/shader.h>
#include <GL/glew.h>

using namespace geli::core;

View::View(Shader& shader) :
    _vMatrix(1.0f),
    _pMatrix(1.0f),
    _shader(shader)
{
    _shader.setVMatrix(_vMatrix);
    _shader.setPMatrix(_pMatrix);
}

void View::orthographic(float l, float r, float b, float t, float n, float f)
{
    _pMatrix = glm::ortho(l, r, b, t, n, f);
    _shader.setPMatrix(_pMatrix);
}
