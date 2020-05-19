#include <geli/camera.hpp>

#include <geli/window.hpp>

using namespace geli;

OrbitCamera::OrbitCamera() :
    _center(0.0f),
    _yaw(0.0f),
    _pitch(0.0f),
    _zoom(1.0f),
    _minPitch(-M_PI*0.499f),
    _maxPitch(M_PI*0.499f),
    _minZoom(1.0f),
    _maxZoom(50.0f),
    _sensitivity(1.0f)
{}

OrbitCamera::OrbitCamera(Window& w) : OrbitCamera()
{
    attach_to(w);
}

void OrbitCamera::attach_to(Window& w)
{
    // add event handler for the mouse
    w.add_on_mouse_drag([this](Window&, const Vec2d&, const Vec2d& rel, int btn)
    {
        if (btn == GLFW_MOUSE_BUTTON_1) {
            // left mouse button, orbit
            set_yaw(_yaw + 0.02f * _sensitivity * rel.x());
            set_pitch(_pitch + 0.02f * _sensitivity * rel.y());
        } else if (btn == GLFW_MOUSE_BUTTON_2) {
            // right mouse button, zoom
            set_zoom(_zoom + 0.02f * _sensitivity * rel.y());
        }
    });
}

Mat4f OrbitCamera::get_view_matrix() const
{
    return Mat4f::look_at(get_position(), _center, Vec3f(0.0f, 1.0f, 0.0f));
}

Vec3f OrbitCamera::get_position() const
{
    Vec3f position(cosf(_yaw), 0.0f, sinf(_yaw));
    position = position * cosf(_pitch);
    position.y() = sinf(_pitch);
    return _zoom * normalize(position);
}

void OrbitCamera::set_pitch_range(const Vec2f& range)
{
    _minPitch = range.x();
    _maxPitch = range.y();
}

void OrbitCamera::set_zoom_range(const Vec2f& range)
{
    _minZoom = range.x();
    _maxZoom = range.y();
}

void OrbitCamera::set_zoom(float z)
{
    _zoom = CLAMP(z, _minZoom, _maxZoom);
}

void OrbitCamera::set_yaw(float y)
{
    _yaw = y;
}

void OrbitCamera::set_pitch(float p)
{
    _pitch = CLAMP(p, _minPitch, _maxPitch);
}
