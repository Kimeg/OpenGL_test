#version 330 core

in vec3 Color;
in vec2 texCoords;
uniform sampler2D texture1;
uniform sampler2D texture2;

out vec4 FragColor;
void main()
{
	vec4 grassColor = texture(texture1, texCoords);
	vec4 boxColor = texture(texture2, texCoords);

	//FragColor = mix(grassColor, boxColor, step(vec4(0.3), grassColor));
	FragColor = mix(grassColor, boxColor, 0.1);
	//gl_FragColor = vec4(1.0f);
}
