/**
 * Contains definitions and initialization of all predefined shaders.
 */

#include <geli/shader.hpp>

#include <iostream>

using namespace geli;

namespace
{
    static const char* VERTEX_SHADER = R"(#version 330
        uniform mat4 u_VP;
        uniform mat4 u_M;
        uniform vec3 u_Color;

        in vec3 v_Position;
        in vec3 v_Normal;
        in vec2 v_UV;

        out vec4 o_Color;

        void main()
        {
            // gl_Position = u_VP * u_M * vec4(v_Position, 1.0);
            // o_Color = vec4(u_Color, 1.0);

            gl_Position = vec4(v_Position, 1.0);
            o_Color = vec4(1.0, 1.0, 1.0, 1.0);
        }
    )";

    static const char* FRAGMENT_SHADER = R"(#version 330
        in vec4 o_Color;

        out vec4 gl_Color;

        void main() {
            gl_Color = o_Color;
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
