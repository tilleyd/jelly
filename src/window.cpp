#include <geli/window.hpp>

#include <chrono>
#include <iostream>
#include <stdexcept>

namespace geli {


Window::Window(const std::string& title, int width, int height) :
    _windowHandle(nullptr),
    _title(title),
    _width(width),
    _height(height),
    _mousePos(0.0f, 0.0f),
    _mouseButton(-1),
    _willExit(false),
    _isActive(false)
{}


Window::~Window() {
    _exit();
}


void Window::create_windowed() {
    if (_windowHandle == nullptr) {
        _start_glfw();
        _windowHandle = glfwCreateWindow(
            _width,
            _height,
            _title.c_str(),
            nullptr,
            nullptr
        );
        if (!_windowHandle) {
            _end_glfw();
            throw std::runtime_error("Could not create window");
        }
        glfwMakeContextCurrent(_windowHandle);
        glfwSetWindowUserPointer(_windowHandle, this);
        _start_glew();
        _setup_events();
        _context = new Context(this);
        if (_createCallback) {
            _createCallback(*this, *_context);
        }
        _draw_loop();
    }
}


void Window::create_borderless() {
    // TODO
    throw std::runtime_error("Borderless fullscreen currently unsupported");
}


void Window::create_fullscreen() {
    if (!_windowHandle) {
        _start_glfw();
        _windowHandle = glfwCreateWindow(
            _width,
            _height,
            _title.c_str(),
            glfwGetPrimaryMonitor(),
            nullptr
        );
        if (!_windowHandle) {
            _end_glfw();
            throw std::runtime_error("Could not create fullscreen window");
        }
        glfwMakeContextCurrent(_windowHandle);
        glfwSetWindowUserPointer(_windowHandle, this);
        _start_glew();
        _setup_events();
        _context = new Context(this);
        if (_createCallback) {
            _createCallback(*this, *_context);
        }
        _draw_loop();
    }
}


void Window::exit() {
    _willExit = true;
}


void Window::set_on_create(create_callback_t cb) {
    _createCallback = cb;
}


void Window::set_on_draw(draw_callback_t cb) {
    _drawCallback = cb;
}


void Window::set_on_close(close_callback_t cb) {
    _closeCallback = cb;
}


void Window::set_on_exit(exit_callback_t cb) {
    _exitCallback = cb;
}


void Window::add_on_key(key_callback_t cb) {
    _keyCallbacks.push_back(cb);
}


void Window::add_on_mouse_button(mouse_button_callback_t cb) {
    _mouseButtonCallbacks.push_back(cb);
}


void Window::add_on_mouse_move(mouse_move_callback_t cb) {
    _mouseMoveCallbacks.push_back(cb);
}


void Window::add_on_mouse_drag(mouse_drag_callback_t cb) {
    _mouseDragCallbacks.push_back(cb);
}


void Window::capture_mouse() {
    glfwSetInputMode(_windowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}


void Window::hide_mouse() {
    glfwSetInputMode(_windowHandle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}


void Window::restore_mouse() {
    glfwSetInputMode(_windowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}


void Window::_start_glfw() {
    if (!glfwInit()) {
        throw std::runtime_error("Could not initialize glfw");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}


void Window::_end_glfw() {
    glfwTerminate();
}


void Window::_start_glew() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_CULL_FACE);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("could not initialize glew");
    }

    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
}


void Window::_setup_events() {
    glfwSetKeyCallback(_windowHandle, _glfw_key_callback);
    glfwSetMouseButtonCallback(_windowHandle, _glfw_mouse_button_callback);
    glfwSetCursorPosCallback(_windowHandle, _glfw_mouse_move_callback);
}


void Window::_draw_loop() {
    _isActive = true;
    auto epoch = std::chrono::high_resolution_clock::now();
    while (!will_exit()) {
        // Draw step: get time passed in seconds, call the draw callback, and swap the double buffers
        auto point = std::chrono::high_resolution_clock::now();
        double period = std::chrono::duration_cast<std::chrono::nanoseconds>(point - epoch).count() * 1.0e-9;
        epoch = point;

        if (_drawCallback) {
            _drawCallback(*this, *_context, period);
        }

        glfwSwapBuffers(_windowHandle);

        // Process events
        glfwPollEvents();

        // Check if the user or system attempted to close
        if (glfwWindowShouldClose(_windowHandle)) {
            if (!_closeCallback || _closeCallback(*this)) {
                exit();
            } else {
                // Closing was overridden by the callback
                glfwSetWindowShouldClose(_windowHandle, false);
            }
        }
    }
    _isActive = false;
    _exit();
}


void Window::_exit() {
    if (_windowHandle) {
        if (_exitCallback) {
            _exitCallback(*this);
        }
        glfwDestroyWindow(_windowHandle);
        _windowHandle = nullptr;
        _end_glfw();
    }
}


/*static*/ void Window::_glfw_key_callback(GLFWwindow* wh, int key, int sc, int act, int mods) {
    Window* w = static_cast<Window*>(glfwGetWindowUserPointer(wh));
    for (key_callback_t& cb : w->_keyCallbacks) {
        cb(*w, key, sc, act, mods);
    }
}


/*static*/ void Window::_glfw_mouse_button_callback(GLFWwindow* wh, int btn, int act, int mods) {
    Window* w = static_cast<Window*>(glfwGetWindowUserPointer(wh));
    for (mouse_button_callback_t& cb : w->_mouseButtonCallbacks) {
        cb(*w, btn, act, mods);
    }
    // Keep track of the last button pressed
    if (act == GLFW_RELEASE && btn == w->_mouseButton) {
        w->_mouseButton = -1;
    } else if (act == GLFW_PRESS) {
        w->_mouseButton = btn;
    }
}


/*static*/ void Window::_glfw_mouse_move_callback(GLFWwindow* wh, double x, double y) {
    Window* w = static_cast<Window*>(glfwGetWindowUserPointer(wh));
    Vec2 pos(x, y);
    Vec2 rel = pos - w->_mousePos;
    w->_mousePos = pos;
    for (mouse_move_callback_t& cb : w->_mouseMoveCallbacks) {
        cb(*w, pos, rel);
    }
    // If a button is held, also call drag callbacks
    if (w->_mouseButton != -1) {
        for (mouse_drag_callback_t& cb : w->_mouseDragCallbacks) {
            cb(*w, pos, rel, w->_mouseButton);
        }
    }
}


}
