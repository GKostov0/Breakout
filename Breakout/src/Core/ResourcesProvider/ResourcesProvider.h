#pragma once

#include <map>
#include <string>

#include<glad\glad.h>

#include "Core\Texture\Texture.h"
#include "Core\Shader\Shader.h"

class ResourcesProvider
{
public:
	static std::map<std::string, Shader> Shaders;
	static std::map<std::string, Texture2D> Textures;

	static Shader LoadShader(const char* vShaderPath, const char* fShaderPath, const char* gShaderPath, std::string id);

	static void Clear();

	static Texture2D GetTexture(std::string name);
	static Shader GetShader(std::string name);
	static Texture2D LoadTexture(const char* filePath, bool alpha, std::string name);

private:
	ResourcesProvider() { }

	static Shader loadShadersFromFile(const char* vShaderPath, const char* fShaderPath, const char* gShaderPath = nullptr);
	static Texture2D loadTextureFromFile(const char* filePath, bool alpha);
};