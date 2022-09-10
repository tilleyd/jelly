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
