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

void Sketch::rect()
{
    _pimpl->rect();
}

void Sketch::stop()
{
    _pimpl->stop();
}
