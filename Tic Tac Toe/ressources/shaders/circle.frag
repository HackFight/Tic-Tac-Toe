#version 330 core

out vec4 FragColor;

in vec2 UV;

uniform vec4 color;

void main()
{
	if (dot(UV, UV) > 1.0f)
	{
		discard;
	}
	
	FragColor = color;
}