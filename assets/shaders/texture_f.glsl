#version 460 core

layout(location = 0) out vec4 color;

in vec2 frag_uv;

uniform sampler2D tex;
uniform vec4 tintColor;

void main()
{
    vec4 texColor = texture(tex, frag_uv);
    color = tintColor * texColor; 
}