#pragma once

#include <iostream>

#include <glad\glad.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

class Shader
{
public:
	unsigned int ID;
	Shader() : ID(0) {}

	Shader& Use();

	// Geometry is optional
	void Compile(const char* vertex, const char* fragment, const char* geometry = nullptr);

	void SetMatrix4(const char* name, const glm::mat4& matrix, bool useShader = false);
	void SetVector3f(const char* name, float x, float y, float z, bool useShader = false);
	void SetVector3f(const char* name, glm::vec3& value, bool useShader = false);

private:
	enum ShaderCompileType
	{
		Vertex = 0, Fragment = 1, Geometry = 2,
		Program = 3
	};

	void CheckCompileStatus(unsigned int object, ShaderCompileType type);
};