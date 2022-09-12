#include <jelly/mixins/canvas.hpp>

#include <stdexcept>

#include <jelly/window.hpp>
#include <jelly/sketch.hpp>

using namespace jelly;

int CanvasMixin::window_width() const {
    return _sketch->jelly_window().get_width();
}

int CanvasMixin::window_height() const {
    return _sketch->jelly_window().get_height();
}

Vec2 CanvasMixin::window_size() const {
    return _sketch->jelly_window().get_size();
}

void CanvasMixin::clear() const {
    _sketch->jelly_context().clear(Vec3(1.0f));
}

void CanvasMixin::clear_rgb(float r, float g, float b) const {
    _sketch->jelly_context().clear(Vec3(r, g, b));
}
