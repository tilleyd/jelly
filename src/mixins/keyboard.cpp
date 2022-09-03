#include <jelly/mixins/keyboard.hpp>

#include <stdexcept>

#include <jelly/window.hpp>
#include <jelly/sketch.hpp>

using namespace jelly;

void KeyboardMixin::init() {
    std::shared_ptr<Window> window = _sketch->jelly_window();
    if (window == nullptr) {
        throw std::runtime_error("Window is not available yet");
    }

    window->add_on_key([this](Window&, int key, int scancode, int action, int modifier) {
        switch (action) {
            case GLFW_PRESS:
                // NOTE: We don't consider GLFW_REPEAT as a pressed key.
                this->_key_pressed[key] = true;
                break;
            case GLFW_RELEASE:
                this->_key_pressed[key] = false;
                break;
            default:
                break;
        }
    });
}

bool KeyboardMixin::key_pressed(int key) const {
    try {
        return _key_pressed.at(key);
    } catch (...) {
        return false;
    }
}
