#pragma once

#include <map>
#include <string>

#include "Core\Shader\Shader.h"

class ResourcesProvider
{
public:
	static std::map<std::string, Shader> Shaders;

	static Shader LoadShader(const char* vShaderPath, const char* fShaderPath, const char* gShaderPath, std::string id);

private:
	ResourcesProvider() { }

	static Shader loadShadersFromFile(const char* vShaderPath, const char* fShaderPath, const char* gShaderPath = nullptr);
};