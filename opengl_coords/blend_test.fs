#version 330 core

in vec2 texCoords;

uniform sampler2D text;

void main()
{
    gl_FragColor = texture(text, texCoords);
}