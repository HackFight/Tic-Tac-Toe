#version 330 core

out vec4 FragColor;

in vec2 UV;

uniform sampler2D tex0;

void main()
{
	vec4 texturePoint = texture(tex0, UV);

	if (texturePoint.a < 0.1f)
	{
		discard;
	}

	FragColor = texturePoint;
}