//
// Created by Sayama on 11/07/2024.
//

#pragma once

namespace Ygg::Meior::Shaders
{
	static constexpr const char* const c_DefaultVert = R"(
#version 450 core

uniform mat4 u_ProjectionMatrix = mat4(1);

uniform vec3 u_CamPos = vec3(0);
uniform vec3 u_CamFwd = vec3(0,0,1);
uniform vec3 u_CamUp = vec3(0,1,0);

uniform mat4 u_ModelMatrix = mat4(1);
uniform mat4 u_NormalMatrix = mat4(1);

in vec3 a_Position;
in vec3 a_Normal;
in vec2 a_TexCoord;
in vec4 a_Color;

out vec3 v_Position;
out vec3 v_Normal;
out vec2 v_TexCoord;
out vec4 v_Color;


void main() {
	vec3 right = normalize(cross(u_CamFwd, u_CamUp));

	mat4 view;
	view[0] = vec4(right, 0);
	view[1] = vec4(u_CamUp, 0);
	view[2] = vec4(u_CamFwd, 0);
	view[3] = vec4(u_CamPos, 1);
	view = inverse(view);

    gl_Position = u_ProjectionMatrix * view * u_ModelMatrix * vec4(a_Position, 1.0);
    v_Position = (u_ModelMatrix * vec4(a_Position, 1.0)).xyz;

    v_Normal = normalize((u_NormalMatrix * vec4(a_Normal, 1.0)).xyz);
    v_TexCoord = a_TexCoord;
    v_Color = a_Color;
}
)";

	static constexpr const char* const c_DefaultFrag = R"(
#version 450 core

uniform vec3 u_CamPos = vec3(0);

uniform sampler2D u_Texture;

in vec3 v_Position;
in vec3 v_Normal;
in vec2 v_TexCoord;
in vec4 v_Color;

out vec4 o_Color;

vec3 CalculateLighting(vec3 lightColor, vec3 lightDir, float lightIntensity)
{
	lightDir = normalize(lightDir);

    // ambient
    float ambientStrength = 0.05 * lightIntensity;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    float diff = max(dot(v_Normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * lightIntensity;

    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(u_CamPos - v_Position);
    vec3 reflectDir = normalize(reflect(-lightDir, v_Normal));
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor * lightIntensity;

    return (ambient + diffuse + specular);
    // return (ambient + diffuse);
}

void main()
{
   o_Color = vec4((v_Normal + 1.0) * 0.5, 1.0);
   o_Color *= texture2D(u_Texture, v_TexCoord);
   o_Color *= vec4(CalculateLighting(vec3(0.9, 0.8, 0.85), vec3(0.5, 1, -0.6), 2.0), 1);
}
)";

}