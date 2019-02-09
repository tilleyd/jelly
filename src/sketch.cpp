#include <geli/sketch.h>

#include <geli/core/sketch_impl.h>

using geli::Sketch;
using geli::core::SketchImpl;

Sketch::Sketch() :
    _pimpl(nullptr)
{
    _pimpl = new SketchImpl;
}

Sketch::~Sketch()
{
    if (_pimpl) {
        delete _pimpl;
    }
}

void Sketch::execute(unsigned int width, unsigned int height)
{
    _pimpl->execute(*this, width, height);
}

void Sketch::background(float r, float g, float b, float a)
{
    _pimpl->background(r, g, b, a);
}

void Sketch::circle(float x, float y, float d)
{
    _pimpl->circle(x, y, d);
}

void Sketch::color(float r, float g, float b, float a)
{
    _pimpl->color(r, g, b, a);
}

void Sketch::ellipse(float x, float y, float w, float h)
{
    _pimpl->ellipse(x, y, w, h);
}

void Sketch::line(float x1, float y1, float x2, float y2)
{
    _pimpl->line(x1, y1, x2, y2);
}

void Sketch::rect(float x, float y, float w, float h)
{
    _pimpl->rect(x, y, w, h);
}

void Sketch::square(float x, float y, float e)
{
    _pimpl->rect(x, y, e, e);
}

void Sketch::stop()
{
    _pimpl->stop();
}

void Sketch::ortho()
{
    _pimpl->ortho();
}

void Sketch::ortho(float l, float r, float b, float t)
{
    _pimpl->ortho(l, r, b, t, -1.0f, 1.0f);
}

void Sketch::ortho(float l, float r, float b, float t, float n, float f)
{
    _pimpl->ortho(l, r, b, t, n, f);
}

unsigned int Sketch::height() const
{
    return _pimpl->height();
}

unsigned int Sketch::width() const
{
    return _pimpl->width();
}
