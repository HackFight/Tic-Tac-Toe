#version 330 core

out vec4 FragColor;

uniform float windowWidth;
uniform float windowHeight;

void main()
{
   float x = gl_FragCoord.x / windowWidth;
   float y = gl_FragCoord.y / windowHeight;

   FragColor = vec4(x, y, 1.0f, 1.0f);
}