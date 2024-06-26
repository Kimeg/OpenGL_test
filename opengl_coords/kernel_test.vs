#version 330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aNormal;
layout (location=2) in vec2 aTex;

out vec3 fragPos;
out vec3 normals;
out vec2 texCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	gl_Position = projection*view*model*vec4(aPos, 1.0f);
	fragPos = vec3(model*vec4(aPos, 1.0f));
	texCoords = aTex;
	normals = aNormal;
}
