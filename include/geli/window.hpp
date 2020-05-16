#ifndef _GELI_WINDOW_HPP_
#define _GELI_WINDOW_HPP_

#include <functional>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <geli/math.hpp>

namespace geli
{

/**
 * A draw loop callback function.
 *
 * \param double
 *     The time passed since the previous draw call.
 */
typedef std::function<void(double)> draw_callback_t;

/**
 * A window close callback function. Should return true to allow the window
 * to exit, or false to override and block the close.
 */
typedef std::function<bool()> close_callback_t;

/**
 * A window exit callback function.
 */
typedef std::function<void()> exit_callback_t;

/**
 * Defines a window used for the rendering environment.
 *
 * \note All callback functions run in the same thread in which the window
 * was created.
 */
class Window
{

public:

    Window() = delete;
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    /**
     * Creates a window with a given title. The window
     *
     * \param title
     *     The title of the window.
     * \param size
     *     The pixel size (width, height) of the window.
     */
    Window(const std::string& title, const Vec2i& size);

    /**
     * Closes and discards the window.
     */
    ~Window();

    /**
     * Creates and shows the window with a fixed size. This passes control to
     * the window's draw loop.
     *
     * \throw std::runtime_error if creation of the window failed.
     */
    void create_windowed();

    /**
     * Creates and shows the window in fullscreen mode. This passes control to
     * the window's draw loop.
     *
     * \throw std::runtime_error if creation of the window failed.
     */
    void create_fullscreen();

    /**
     * Marks the window to exit after completion of the current draw step.
     */
    void exit();

    /**
     * Sets a callback function to be called at each draw step.
     */
    void on_draw(draw_callback_t);

    /**
     * Sets a callback function to be called when the window is closed by the
     * user or system, allowing to optionally bypass the decision.
     */
    void on_close(close_callback_t);

    /**
     * Sets a callback function to be called when the window is exited.
     */
    void on_exit(exit_callback_t);

    /**
     * Returns the size of the window.
     */
    Vec2i get_size()
    {
        return _size;
    }

    /**
     * Returns true if the window will exit at the end of the current draw step.
     */
    bool will_exit()
    {
        return _willExit;
    }

    /**
     * Returns true if the window is currently executing the draw loop.
     */
    bool is_active()
    {
        return _isActive;
    }

    /**
     * Returns the raw GLFW window handle.
     */
    GLFWwindow* get_glfw_handle()
    {
        return _windowHandle;
    }

private:

    GLFWwindow*  _windowHandle;
    std::string  _title;
    Vec2i        _size;

    bool _willExit, _isActive;

    draw_callback_t  _draw_callback;
    close_callback_t _close_callback;
    exit_callback_t  _exit_callback;

    void _start_glfw();

    void _end_glfw();

    void _start_glew();

    void _draw_loop();

    void _exit();

};

};

#endif
