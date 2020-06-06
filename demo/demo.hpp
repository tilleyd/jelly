#ifndef _DEMO_H_
#define _DEMO_H_

#include <memory>

#include <geli/camera.hpp>
#include <geli/framebuffer.hpp>
#include <geli/mesh.hpp>
#include <geli/shader.hpp>
#include <geli/texture.hpp>
#include <geli/window.hpp>

class Demo
{

public:

    void create(geli::Window&, geli::Renderer&);

    void draw(geli::Window&, geli::Renderer&, double p);

    void on_key(geli::Window&, int, int, int, int);

    void on_mouse_move(geli::Window&, const geli::Vec2d&, const geli::Vec2d&);

private:

    int _counter;

    geli::OrbitCamera _camera;

    std::shared_ptr<geli::Renderable> _sphere;
    std::shared_ptr<geli::Renderable> _redLight;
    std::shared_ptr<geli::Renderable> _greenLight;
    std::shared_ptr<geli::Renderable> _blueLight;
    std::shared_ptr<geli::Renderable> _platform;

};

#endif
