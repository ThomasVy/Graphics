#version 460 core

layout(location = 0) out vec4 color;

in vec2 v_texCoord;
in float v_texId;

uniform sampler2D u_texture[2];

void main()
{
    int index = int(v_texId);
    color = texture(u_texture[index], v_texCoord);
};    
