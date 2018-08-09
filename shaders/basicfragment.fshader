#version 150 core

in vec3 Color;
in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D tex;

void main() 
{
	if(texture(tex, Texcoord).a < 1.0f)
		outColor = texture(tex, Texcoord);
	else
		outColor = mix(texture(tex, Texcoord), vec4(Color, 1.0f), 0.5f);
}