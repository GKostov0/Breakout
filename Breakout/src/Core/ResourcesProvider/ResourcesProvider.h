#pragma once

#include <map>
#include <string>

#include "Core\Shader\Shader.h"

class ResourcesProvider
{
public:
	static std::map<std::string, Shader> Shaders;

private:
	ResourcesProvider() { }

	Shader loadShadersFromFile(const char* vShaderPath, const char* fShaderPath, const char* gShaderPath = nullptr);
};