/**
 * Contains definitions and initialization of all predefined shaders.
 */

#include <geli/shader.hpp>

#include <iostream>

using namespace geli;

namespace
{
    static const char* VERTEX_SHADER = R"(#version 330
        layout (location = 0) in vec3 v_Position;
        layout (location = 1) in vec3 v_Normal;
        layout (location = 2) in vec2 v_UV;

        uniform mat4 u_M;
        uniform mat4 u_V;
        uniform mat4 u_P;
        uniform vec3 u_Color = vec3(1.0, 1.0, 1.0);

        out vec4 o_Color;
        out vec2 o_UV;

        void main()
        {
            gl_Position = u_P * u_V * u_M * vec4(v_Position, 1.0);
            o_Color = vec4(u_Color, 1.0);
            o_UV = v_UV;
        }
    )";

    static const char* FRAGMENT_SHADER = R"(#version 330
        in vec4 o_Color;
        in vec2 o_UV;

        uniform sampler2D u_TexDiffuse;

        out vec4 gl_Color;

        void main() {
            gl_Color = o_Color * texture(u_TexDiffuse, o_UV);
        }
    )";
}

std::shared_ptr<Shader> Shader::_defaultShader = nullptr;

std::shared_ptr<Shader> Shader::default_shader()
{
    if (!_defaultShader) {
        _defaultShader = std::make_shared<Shader>(VERTEX_SHADER, FRAGMENT_SHADER);
    }
    return _defaultShader;
}
