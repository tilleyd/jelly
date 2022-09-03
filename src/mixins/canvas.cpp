#include <jelly/mixins/canvas.hpp>

#include <stdexcept>

#include <jelly/window.hpp>
#include <jelly/sketch.hpp>

using namespace jelly;

int CanvasMixin::window_width() const {
    return _try_get_window()->get_width();
}

int CanvasMixin::window_height() const {
    return _try_get_window()->get_height();
}

Vec2 CanvasMixin::window_size() const {
    return _try_get_window()->get_size();
}

std::shared_ptr<Window> CanvasMixin::_try_get_window() const {
    std::shared_ptr<Window> window = _sketch->jelly_window();
    if (window == nullptr) {
        throw std::runtime_error("Window is not available yet");
    }
    return window;
}
