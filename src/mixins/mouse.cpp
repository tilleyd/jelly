#include <jelly/mixins/mouse.hpp>

#include <stdexcept>

#include <jelly/window.hpp>
#include <jelly/sketch.hpp>

using namespace jelly;

void MouseMixin::init() {
    std::shared_ptr<Window> window = _sketch->jelly_window();
    if (window == nullptr) {
        throw std::runtime_error("Window is not available yet");
    }

    window->add_on_mouse_button([this](Window&, int button, int action, int modifier) {
        switch (action) {
            case GLFW_PRESS:
                this->_button_pressed[button] = true;
                break;
            case GLFW_RELEASE:
                this->_button_pressed[button] = false;
                break;
            default:
                break;
        }
    });

    window->add_on_mouse_move([this](Window&, Vec2 position, Vec2 relative) {
        this->_mouse_position = position;
    });
}

bool MouseMixin::mouse_button_pressed(int button) const {
    try {
        return _button_pressed.at(button);
    } catch (...) {
        return false;
    }
}
