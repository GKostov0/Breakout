#pragma once

#include <iostream>

#include <glad\glad.h>

class Shader
{
public:
	unsigned int ID;
	Shader() : ID(0) {}

	// Geometry is optional
	void Compile(const char* vertex, const char* fragment, const char* geometry = nullptr);

private:
	enum ShaderCompileType
	{
		Vertex = 0, Fragment = 1, Geometry = 2,
		Program = 3
	};

	void CheckCompileStatus(unsigned int object, ShaderCompileType type);
};