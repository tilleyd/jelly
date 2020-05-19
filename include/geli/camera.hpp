#ifndef _GELI_CAMERA_HPP_
#define _GELI_CAMERA_HPP_

#include <geli/math.hpp>

namespace geli
{

class Window;

/**
 * Creates an orbit camera that can be attached to a window and controlled using
 * the mouse.
 */
class OrbitCamera
{

public:

    /**
     * Creates a default orbit camera.
     */
    OrbitCamera();

    /**
     * Creates a default orbit camera and attaches it to the given window.
     */
    OrbitCamera(Window&);

    /**
     * Adds input events to listen to mouse behaviour from the provided window.
     */
    void attach_to(Window&);

    /**
     * Calculates and returns the view matrix of the camera.
     */
    Mat4f get_view_matrix() const;

    /**
     * Calculates and returns the position of the camera.
     */
    Vec3f get_position() const;

    /**
     * Sets the point around which the camera orbits.
     */
    void set_orbit_center(const Vec3f& center)
    {
        _center = center;
    }

    /**
     * Sets the yaw value in radians.
     */
    void set_yaw(float y);

    /**
     * Sets the pitch value in radians, clamped to the pitch range.
     */
    void set_pitch(float p);

    /**
     * Sets the zoom value, clamped to the zoom range.
     */
    void set_zoom(float z);

    /**
     * Sets the range of allowed pitch values. The default is slightly smaller
     * than (-pi/2.5, pi/2.5) to avoid gimbal lock.
     *
     * \param range
     *     The (min, max) pitch values in radians.
     */
    void set_pitch_range(const Vec2f& range);

    /**
     * Sets the range of allowed zoom distances. The default is (1, 50).
     *
     * \param range
     *     The (min, max) allowed zoom distances.
     */
    void set_zoom_range(const Vec2f& range);

    /**
     * Sets the mouse sensitivity. The default is 1.0.
     */
    void set_sensitivity(float s) { _sensitivity = s; }

    Vec3f get_orbit_center() const { return _center; }

    float get_yaw() const { return _yaw; }

    float get_pitch() const { return _pitch; }

    float get_zoom() const { return _zoom; }

    Vec2f get_pitch_range() const { return Vec2f(_minPitch, _maxPitch); }

    Vec2f get_zoom_range() const { return Vec2f(_minZoom, _maxZoom); }

    float get_sensitivity() const { return _sensitivity; }

private:

    Vec3f _center;
    float _yaw;
    float _pitch;
    float _zoom;
    float _minPitch;
    float _maxPitch;
    float _minZoom;
    float _maxZoom;
    float _sensitivity;

};

};

#endif
