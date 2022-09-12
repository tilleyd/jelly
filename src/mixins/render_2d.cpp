#include <jelly/mixins/render_2d.hpp>

#include <jelly/sketch.hpp>
#include <jelly/gl/context.hpp>
#include <jelly/gl/mesh.hpp>
#include <jelly/gl/shader.hpp>

using namespace jelly;

const std::string BLIT_VS = R"(
    #version 330

    layout (location = 0) in vec3 v_Position;
    layout (location = 1) in vec3 v_Normal;
    layout (location = 2) in vec2 v_UV;

    uniform mat4 u_Projection;
    uniform vec4 u_Rectangle;

    out vec2 o_UV;

    void main() {
        o_UV = v_UV;

        vec3 scale = vec3(
            u_Rectangle.z - u_Rectangle.x,
            u_Rectangle.w - u_Rectangle.y,
            1.0
        );
        vec3 offset = vec3(u_Rectangle.xy, 0.0);
        gl_Position = u_Projection * vec4(scale * v_Position + offset, 1.0);
    }
)";

const std::string RECTANGLE_FS = R"(
    #version 330

    uniform vec4 u_Color;

    out vec4 o_Color;

    void main() {
        o_Color = u_Color;
    }
)";

const std::string ELLIPSE_FS = R"(
    #version 330

    in vec2 o_UV;

    uniform vec4 u_Color;

    out vec4 o_Color;

    void main() {
        vec2 v = 2 * o_UV - 1;
        if (dot(v, v) > 1) {
            discard;
        }
        o_Color = u_Color;
    }
)";


Render2DMixin::~Render2DMixin() {
    if (_rectangle_shader) {
        delete _rectangle_shader;
        _rectangle_shader = nullptr;
    }
    if (_ellipse_shader) {
        delete _ellipse_shader;
        _ellipse_shader = nullptr;
    }
    if (_quad_mesh) {
        delete _quad_mesh;
        _quad_mesh = nullptr;
    }
}


void Render2DMixin::init() {
    _rectangle_shader = new Shader(BLIT_VS, RECTANGLE_FS);
    _ellipse_shader = new Shader(BLIT_VS, ELLIPSE_FS);
    _quad_mesh = Mesh::quad_mesh();
}


void Render2DMixin::set_fill_rgb(float r, float g, float b) {
    set_fill_rgba(r, g, b, 1.0f);
}


void Render2DMixin::set_fill_rgba(float r, float g, float b, float a) {
    _rectangle_shader->set_uniform_vec4("u_Color", Vec4(r, g, b, a));
    _ellipse_shader->set_uniform_vec4("u_Color", Vec4(r, g, b, a));
}


void Render2DMixin::set_fill_value(float value) {
    set_fill_rgba(value, value, value, 1.0f);
}


void Render2DMixin::fill_rectangle(int x1, int y1, int x2, int y2) {
    Context& c = _sketch->jelly_context();
    c.activate_shader(*_rectangle_shader);
    _rectangle_shader->set_uniform_vec4("u_Rectangle", Vec4(x1, y1, x2, y2));
    _rectangle_shader->set_uniform_mat4("u_Projection", _sketch->projection_mat());
    c.render_mesh(*_quad_mesh);
}


void Render2DMixin::fill_ellipse(int x, int y, int w, int h) {
    Context& c = _sketch->jelly_context();
    c.activate_shader(*_ellipse_shader);
    _ellipse_shader->set_uniform_vec4(
        "u_Rectangle",
        Vec4(x - w / 2, y - h / 2, x + w / 2, y + h / 2)
    );
    _ellipse_shader->set_uniform_mat4("u_Projection", _sketch->projection_mat());
    c.render_mesh(*_quad_mesh);
}
