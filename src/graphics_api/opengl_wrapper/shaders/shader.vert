#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in float texId;
layout(location = 3) in mat4 model;

out vec2 v_texCoord;
out float v_texId;
uniform mat4 u_PV;

void main()
{
    gl_Position = u_PV * model * vec4(position, 1.0);
    v_texCoord = texCoord;
    v_texId = texId; 
};
