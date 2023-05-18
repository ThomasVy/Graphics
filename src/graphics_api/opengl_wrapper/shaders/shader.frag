#version 460 core

layout(location = 0) out vec4 color;

in vec2 v_texCoord;

uniform sampler2D u_texture[3];
uniform uint u_texId;
uniform bool u_useSolidColor;
void main()
{
    if (u_useSolidColor)
    {
        color = vec4(1.0, 0.0, 0.0, 1.0);
    }
    else
    {
        color = texture(u_texture[u_texId], v_texCoord);
    }
};    
