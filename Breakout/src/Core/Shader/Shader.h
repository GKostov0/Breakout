#pragma once

#include <string>

#include <glad\glad.h>

class Shader
{
public:
	unsigned int ID;
	Shader() {}

	void Compile();
};