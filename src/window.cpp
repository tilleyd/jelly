#include <geli/window.hpp>

#include <chrono>
#include <iostream>
#include <stdexcept>

#include <geli/shader.hpp>

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
            _end_glfw();
            throw std::runtime_error("could not create window");
        }
        glfwMakeContextCurrent(_windowHandle);
        _start_glew();
        if (_createCallback) {
            _createCallback(*this);
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
            _end_glfw();
            throw std::runtime_error("could not create fullscreen window");
        }
        glfwMakeContextCurrent(_windowHandle);
        _start_glew();
        if (_createCallback) {
            _createCallback(*this);
        }
        _draw_loop();
    }
}

void Window::exit()
{
    _willExit = true;
}

void Window::on_create(create_callback_t cb)
{
    _createCallback = cb;
}

void Window::on_draw(draw_callback_t cb)
{
    _drawCallback = cb;
}

void Window::on_close(close_callback_t cb)
{
    _closeCallback = cb;
}

void Window::on_exit(exit_callback_t cb)
{
    _exitCallback = cb;
}

void Window::_start_glfw()
{
    if (!glfwInit()) {
        throw std::runtime_error("could not initialize glfw");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Window::_end_glfw()
{
    // glfwTerminate(); TODO uncomment, the version currently used causes a segfault
}

void Window::_start_glew()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("could not initialize glew");
    }

    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

    Shader::default_shader()->use();
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
        if (_drawCallback) {
            _drawCallback(*this, period);
        }
        glfwSwapBuffers(_windowHandle);

        // process events
        glfwPollEvents();

        // check if the user or system attempted to close
        if (glfwWindowShouldClose(_windowHandle)) {
            if (!_closeCallback || _closeCallback(*this)) {
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
        if (_exitCallback) {
            _exitCallback(*this);
        }
        glfwDestroyWindow(_windowHandle);
        _windowHandle = nullptr;
        _end_glfw();
    }
}
