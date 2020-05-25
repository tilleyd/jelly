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

        uniform mat4 u_ModelMatrix;
        uniform mat4 u_ViewProjMatrix;
        uniform mat3 u_NormalMatrix;

        out vec3 o_Position;
        out vec3 o_Normal;
        out vec2 o_UV;
        void main()
        {
            vec4 worldPosition = u_ModelMatrix * vec4(v_Position, 1.0);

            gl_Position = u_ViewProjMatrix * worldPosition;

            o_Position = worldPosition.xyz;
            o_Normal = u_NormalMatrix * v_Normal;
            o_UV = v_UV;
        }
    )";

    static const char* FRAGMENT_SHADER = R"(#version 330
        in vec3 o_Position;
        in vec3 o_Normal;
        in vec2 o_UV;

        uniform vec3 u_Diffuse = vec3(0.0);
        uniform vec3 u_Emissive = vec3(0.0);
        uniform vec3 u_Specular = vec3(0.0);
        uniform float u_Shininess = 0.0;

        uniform sampler2D u_TexDiffuse;
        uniform sampler2D u_TexSpecular;
        uniform sampler2D u_TexEmissive;
        uniform sampler2D u_TexShininess;

        uniform vec3 u_CameraPosition;

        struct Fragment
        {
            vec3 position;
            vec3 normal;
            vec3 diffuse;
            vec3 specular;
            vec3 emissive;
            float shininess;
        };

        struct DirectionalLight
        {
            vec3 direction;
            vec3 color;
        };

        uniform DirectionalLight u_DirectionalLight;

        struct PointLight
        {
            vec3 position;
            vec3 color;

            float constant;
            float linear;
            float quadratic;
        };

        uniform vec3 u_AmbientLight = vec3(1.0);
        #define POINT_LIGHTS 4
        uniform PointLight u_PointLights[POINT_LIGHTS];

        vec3 directional_light_contribution(DirectionalLight light, Fragment frag)
        {
            vec3 lightDirection = normalize(-light.direction);

            // diffuse light
            float diff = max(0.0, dot(lightDirection, normalize(frag.normal)));
            vec3 lightDiffuse = diff * light.color * frag.diffuse;

            // specular light
            vec3 reflection = reflect(-lightDirection, frag.normal);
            vec3 viewDirection = normalize(u_CameraPosition - frag.position);
            float spec = pow(max(0.0, dot(viewDirection, reflection)), frag.shininess);
            vec3 lightSpecular = spec * light.color * frag.specular;

            return lightDiffuse + lightSpecular;
        }

        vec3 point_light_contribution(PointLight light, Fragment frag)
        {
            vec3 fragToLight = light.position - frag.position;
            vec3 lightDirection = normalize(fragToLight);

            // diffuse light
            float diff = max(0.0, dot(lightDirection, frag.normal));
            vec3 lightDiffuse = diff * light.color * frag.diffuse;

            // specular light
            vec3 reflection = reflect(-lightDirection, frag.normal);
            vec3 viewDirection = normalize(u_CameraPosition - frag.position);
            float spec = pow(max(0.0, dot(viewDirection, reflection)), frag.shininess);
            vec3 lightSpecular = spec * light.color * frag.specular;

            // attenuation
            float distance = length(fragToLight);
            float attenuation = light.constant + light.linear*distance + light.quadratic * (distance*distance);
            attenuation = 1.0 / max(1.0, attenuation);

            return attenuation * (lightDiffuse + lightSpecular);
        }

        out vec4 gl_Color;
        void main()
        {
            Fragment frag;
            frag.position = o_Position;
            frag.normal = normalize(o_Normal);
            frag.diffuse = u_Diffuse + texture(u_TexDiffuse, o_UV).xyz;
            frag.specular = u_Specular + texture(u_TexSpecular, o_UV).xyz;
            frag.emissive = u_Emissive + texture(u_TexEmissive, o_UV).xyz;
            frag.shininess = max(1.000, u_Shininess + texture(u_TexShininess, o_UV).x);

            vec3 light = directional_light_contribution(u_DirectionalLight, frag);

            for (int i = 0; i < POINT_LIGHTS; ++i) {
                light += point_light_contribution(u_PointLights[i], frag);
            }

            light += u_AmbientLight * frag.diffuse;

            gl_Color = vec4(light + frag.emissive, 1.0);
        }
    )";
}

std::shared_ptr<Shader> Shader::create_default_shader()
{
    std::shared_ptr<Shader> shader = std::make_shared<Shader>();
    shader->add_vertex_shader(VERTEX_SHADER);
    shader->add_fragment_shader(FRAGMENT_SHADER);
    shader->link_shaders();
    return shader;
}
