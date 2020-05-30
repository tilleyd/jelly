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

    void create(geli::Window&);

    void draw(geli::Window&, double p);

    void on_key(geli::Window&, int, int, int, int);

    void on_mouse_move(geli::Window&, const geli::Vec2d&, const geli::Vec2d&);

private:

    int _counter;

    geli::OrbitCamera _camera;

    std::shared_ptr<geli::Mesh> _squareMesh;
    std::shared_ptr<geli::Mesh> _sphereMesh;
    std::shared_ptr<geli::Mesh> _cubeMesh;

    std::shared_ptr<geli::Shader> _geomShader;
    std::shared_ptr<geli::Shader> _skyboxShader;
    std::shared_ptr<geli::Shader> _bloomShader;
    std::shared_ptr<geli::Shader> _postShader;

    std::shared_ptr<geli::Texture> _emptyTexture;
    std::shared_ptr<geli::Texture> _woodTexture;

    std::shared_ptr<geli::Framebuffer> _framebuffer;
    std::shared_ptr<geli::Texture>     _colorBuffer1;
    std::shared_ptr<geli::Texture>     _colorBuffer2;
    std::shared_ptr<geli::Texture>     _colorBuffer3;
    std::shared_ptr<geli::Texture>     _depthBuffer;
    std::shared_ptr<geli::Texture>     _skyboxCube;

    geli::Mat4f _projMatrix;

};

#endif
