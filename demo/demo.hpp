#ifndef _DEMO_H_
#define _DEMO_H_

#include <memory>

#include <geli/camera.hpp>
#include <geli/mesh.hpp>
#include <geli/texture.hpp>
#include <geli/window.hpp>

class Demo
{

public:

    void create(geli::Window&);

    void draw(geli::Window&, double p);

    void on_key(geli::Window&, int, int, int, int);

    void on_mouse_move(geli::Window&, const geli::Vec2d&, const geli::Vec2d&);

private:

    int _counter;

    geli::OrbitCamera              _camera;
    std::shared_ptr<geli::Mesh>    _cubeMesh;
    std::shared_ptr<geli::Texture> _woodTexture;
    std::shared_ptr<geli::Texture> _maskTexture;

};

#endif
