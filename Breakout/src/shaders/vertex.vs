#version 330 core

// vec2 positions, vec2 texCoords
layout (location = 0) in vec4 vertex;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 proj;

void main()
{
	TexCoords = vertex.zw;
	gl_Position = proj * model * vec4(vertexxy, 0.0f, 1.0f);
}