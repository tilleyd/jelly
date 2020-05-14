#include <geli/window.hpp>

#include <stdexcept>
#include <chrono>

using namespace geli;

Window::Window(const std::string& title, const Vec2i& size) :
        _windowHandle(nullptr),
        _title(title),
        _size(size),
        _willExit(false),
        _isActive(false)
{}

Window::~Window()
{
    _exit();
}

void Window::create_windowed()
{
    if (!_windowHandle) {
        _start_glfw();
        _windowHandle = glfwCreateWindow(_size.x(), _size.y(),
                                         _title.c_str(),
                                         nullptr,
                                         nullptr);
        if (!_windowHandle) {
            throw std::runtime_error("could not create window");
        }
        _draw_loop();
    }
}

void Window::create_fullscreen()
{
    if (!_windowHandle) {
        _start_glfw();
        _windowHandle = glfwCreateWindow(_size.x(), _size.y(),
                                        _title.c_str(),
                                        glfwGetPrimaryMonitor(),
                                        nullptr);
        if (!_windowHandle) {
            throw std::runtime_error("could not create fullscreen window");
        }
        _draw_loop();
    }
}

void Window::exit()
{
    _willExit = true;
}

void Window::on_draw(draw_callback_t cb)
{
    _draw_callback = cb;
}

void Window::on_close(close_callback_t cb)
{
    _close_callback = cb;
}

void Window::on_exit(exit_callback_t cb)
{
    _exit_callback = cb;
}

void Window::_start_glfw()
{
    if (!glfwInit()) {
        throw std::runtime_error("could not initialize rendering context");
    }
}

void Window::_end_glfw()
{
    glfwTerminate();
}

void Window::_draw_loop()
{
    _isActive = true;
    auto epoch = std::chrono::high_resolution_clock::now();
    while (!will_exit()) {
        // draw step: get time passed in seconds, call the draw callback and swap the double buffers
        auto point = std::chrono::high_resolution_clock::now();
        double period = std::chrono::duration_cast<std::chrono::nanoseconds>(point - epoch).count() * 1.0e-9;
        epoch = point;
        if (_draw_callback) {
            _draw_callback(period);
        }
        glfwSwapBuffers(_windowHandle);

        // process events
        glfwPollEvents();

        // check if the user or system attempted to close
        if (glfwWindowShouldClose(_windowHandle)) {
            if (!_close_callback || _close_callback()) {
                exit();
            } else {
                // closing was overridden by the callback
                glfwSetWindowShouldClose(_windowHandle, false);
            }
        }
    }
    _isActive = false;
    _exit();
}

void Window::_exit()
{
    if (_windowHandle) {
        if (_exit_callback) {
            _exit_callback();
        }
        glfwDestroyWindow(_windowHandle);
        _windowHandle = nullptr;
        _end_glfw();
    }
}
