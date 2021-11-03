#include "demo.hpp"

#include <cmath>
#include <fstream>

#include <geli/math.hpp>

using namespace geli;


Demo::Demo() :
    _shader(nullptr),
    _square(nullptr),
    _wood(nullptr),
    _colorBuffer(nullptr),
    _framebuffer(nullptr)
{}


Demo::~Demo() {
    if (_shader) {
        delete _shader;
    }
    if (_square) {
        delete _square;
    }
    if (_wood) {
        delete _wood;
    }
    if (_colorBuffer) {
        delete _colorBuffer;
    }
    if (_framebuffer) {
        delete _framebuffer;
    }
}


void Demo::create(Window& w, Context& c) {
    std::string vs = load_file("../demo/vertex.glsl");
    std::string fs = load_file("../demo/fragment.glsl");

    _shader = new Shader(vs, fs);
    _square = Mesh::square_mesh();
    _wood = new Texture("../res/wood.png");

    c.activate_shader(*_shader);

    _colorBuffer = new Texture(640, 360);
    _framebuffer = new Framebuffer();
    _framebuffer->attach_color(*_colorBuffer);
}


void Demo::draw(Window& w, Context& c, double p) {
    c.clear(Vec3(0.1f, 0.2f, 0.3f));
    c.set_framebuffer(*_framebuffer);
    _shader->set_uniform_sampler("u_TexDiffuse", *_wood);
    c.render_mesh(*_square);
    c.reset_framebuffer();
    _shader->set_uniform_sampler("u_TexDiffuse", *_colorBuffer);
    c.render_mesh(*_square);
}


void Demo::on_key(Window&, int key, int, int act, int) {
}


void Demo::on_mouse_move(Window&, const Vec2& p, const Vec2& r) {
}


std::string Demo::load_file(const std::string& path) const {
    std::ifstream file(path);
    if (file.good()) {
        return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    } else {
        throw std::runtime_error("Could not open '" + path + "'");
    }
}
