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

const std::string FILL_RECTANGLE_FS = R"(
    #version 330

    uniform vec4 u_Color;

    out vec4 o_Color;

    void main() {
        o_Color = u_Color;
    }
)";

const std::string DRAW_RECTANGLE_FS = R"(
    #version 330

    in vec2 o_UV;

    uniform vec4 u_Color;
    uniform vec2 u_PixelSize;
    uniform int u_PixelStroke;

    out vec4 o_Color;

    void main() {
        vec2 coords = u_PixelSize * o_UV;
        if (
            coords.x > u_PixelStroke &&
            coords.x < u_PixelSize.x - u_PixelStroke &&
            coords.y > u_PixelStroke &&
            coords.y < u_PixelSize.y - u_PixelStroke
        ) {
            discard;
        }
        o_Color = u_Color;
    }
)";

const std::string FILL_ELLIPSE_FS = R"(
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

const std::string DRAW_ELLIPSE_FS = R"(
    #version 330

    in vec2 o_UV;

    uniform vec4 u_Color;
    uniform vec2 u_PixelSize;
    uniform int  u_PixelStroke;

    out vec4 o_Color;

    void main() {
        vec2 coords = u_PixelSize * o_UV;
        vec2 v = 2 * o_UV - 1;
        vec2 edge = normalize(v);
        vec2 edge_coords = u_PixelSize * (edge + 1) * 0.5;
        vec2 from_edge = coords - edge_coords;
        float dist2 = dot(from_edge, from_edge);
        if (dot(v, v) > 1) {
            discard;
        }
        if (dist2 > u_PixelStroke * u_PixelStroke) {
            discard;
        }
        o_Color = u_Color;
    }
)";


Render2DMixin::Render2DMixin(Sketch* sketch):
    _sketch(sketch),
    _color(0.0, 0.0, 0.0, 1.0),
    _stroke_size(1)
{}


Render2DMixin::~Render2DMixin() {
    if (_fill_rectangle_shader) {
        delete _fill_rectangle_shader;
        _fill_rectangle_shader = nullptr;
    }
    if (_fill_ellipse_shader) {
        delete _fill_ellipse_shader;
        _fill_ellipse_shader = nullptr;
    }
    if (_draw_rectangle_shader) {
        delete _draw_rectangle_shader;
        _draw_rectangle_shader = nullptr;
    }
    if (_draw_ellipse_shader) {
        delete _draw_ellipse_shader;
        _draw_ellipse_shader = nullptr;
    }
    if (_quad_mesh) {
        delete _quad_mesh;
        _quad_mesh = nullptr;
    }
}


void Render2DMixin::init() {
    _fill_rectangle_shader = new Shader(BLIT_VS, FILL_RECTANGLE_FS);
    _draw_rectangle_shader = new Shader(BLIT_VS, DRAW_RECTANGLE_FS);
    _fill_ellipse_shader = new Shader(BLIT_VS, FILL_ELLIPSE_FS);
    _draw_ellipse_shader = new Shader(BLIT_VS, DRAW_ELLIPSE_FS);
    _quad_mesh = Mesh::quad_mesh();
}


void Render2DMixin::set_color(float r, float g, float b) {
    set_color(r, g, b, 1.0f);
}


void Render2DMixin::set_color(float r, float g, float b, float a) {
    _color = Vec4(r, g, b, a);
}


void Render2DMixin::set_color(float value) {
    set_color(value, value, value, 1.0f);
}


void Render2DMixin::set_stroke_size(int stroke) {
    _stroke_size = stroke;
}


void Render2DMixin::fill_rectangle(int x1, int y1, int x2, int y2) {
    Context& c = _sketch->jelly_context();
    c.activate_shader(*_fill_rectangle_shader);
    _fill_rectangle_shader->set_uniform_vec4("u_Color", _color);
    _fill_rectangle_shader->set_uniform_vec4("u_Rectangle", Vec4(x1, y1, x2, y2));
    _fill_rectangle_shader->set_uniform_mat4("u_Projection", _sketch->projection_mat());
    c.render_mesh(*_quad_mesh);
}


void Render2DMixin::draw_rectangle(int x1, int y1, int x2, int y2) {
    Context& c = _sketch->jelly_context();
    c.activate_shader(*_draw_rectangle_shader);
    _draw_rectangle_shader->set_uniform_vec4("u_Color", _color);
    _draw_rectangle_shader->set_uniform_int("u_PixelStroke", _stroke_size);
    _draw_rectangle_shader->set_uniform_vec2("u_PixelSize", Vec2(x2 - x1, y2 - y1));
    _draw_rectangle_shader->set_uniform_vec4("u_Rectangle", Vec4(x1, y1, x2, y2));
    _draw_rectangle_shader->set_uniform_mat4("u_Projection", _sketch->projection_mat());
    c.render_mesh(*_quad_mesh);
}


void Render2DMixin::fill_ellipse(int x, int y, int w, int h) {
    Context& c = _sketch->jelly_context();
    c.activate_shader(*_fill_ellipse_shader);
    _fill_ellipse_shader->set_uniform_vec4("u_Color", _color);
    _fill_ellipse_shader->set_uniform_vec4(
        "u_Rectangle",
        Vec4(x - w / 2, y - h / 2, x + w / 2, y + h / 2)
    );
    _fill_ellipse_shader->set_uniform_mat4("u_Projection", _sketch->projection_mat());
    c.render_mesh(*_quad_mesh);
}


void Render2DMixin::draw_ellipse(int x, int y, int w, int h) {
    Context& c = _sketch->jelly_context();
    c.activate_shader(*_draw_ellipse_shader);
    _draw_ellipse_shader->set_uniform_vec4("u_Color", _color);
    _draw_ellipse_shader->set_uniform_int("u_PixelStroke", _stroke_size);
    _draw_ellipse_shader->set_uniform_vec2("u_PixelSize", Vec2(w, h));
    _draw_ellipse_shader->set_uniform_vec4(
        "u_Rectangle",
        Vec4(x - w / 2, y - h / 2, x + w / 2, y + h / 2)
    );
    _draw_ellipse_shader->set_uniform_mat4("u_Projection", _sketch->projection_mat());
    c.render_mesh(*_quad_mesh);
}
