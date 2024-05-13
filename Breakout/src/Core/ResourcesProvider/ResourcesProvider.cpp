#include "ResourcesProvider.h"

#include <iostream>
#include <sstream>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::map<std::string, Shader> ResourcesProvider::Shaders;
std::map<std::string, Texture2D> ResourcesProvider::Textures;

Shader ResourcesProvider::LoadShader(const char* vShaderPath, const char* fShaderPath, const char* gShaderPath, std::string id)
{
	Shaders[id] = loadShadersFromFile(vShaderPath, fShaderPath, gShaderPath);
	return Shaders[id];
}

void ResourcesProvider::Clear()
{
	for (auto i : Shaders)
	{
		glDeleteProgram(i.second.ID);
	}
}

Shader ResourcesProvider::loadShadersFromFile(const char* vShaderPath, const char* fShaderPath, const char* gShaderPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;

	try
	{
		// Vertex
		std::ifstream vShaderFile(vShaderPath);
		std::stringstream vShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		vShaderFile.close();
		vertexCode = vShaderStream.str();

		// Fragment
		std::ifstream fShaderFile(fShaderPath);
		std::stringstream fShaderStream;
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fragmentCode = fShaderStream.str();

		// Geometry
		if (gShaderPath != nullptr)
		{
			std::ifstream gShaderFile(gShaderPath);
			std::stringstream gShaderStream;
			gShaderStream << gShaderFile.rdbuf();
			gShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (std::exception e)
	{
		std::cout << "[Error]: Failed to read shaders file. Reason:\n" << e.what() << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	const char* gShaderCode = geometryCode.c_str();

	Shader result;
	result.Compile(vShaderCode, fShaderCode, gShaderPath != nullptr ? gShaderCode : nullptr);

	return result;
}

Texture2D ResourcesProvider::GetTexture(std::string name)
{
	return Textures[name];
}

Shader ResourcesProvider::GetShader(std::string name)
{
	return Shaders[name];
}

Texture2D ResourcesProvider::LoadTexture(const char* filePath, bool alpha, std::string name)
{
	Textures[name] = loadTextureFromFile(filePath, alpha);
	return Textures[name];
}

Texture2D ResourcesProvider::loadTextureFromFile(const char* filePath, bool alpha)
{
	Texture2D texture;
	if (alpha)
	{
		texture.internal_format = GL_RGBA;
		texture.image_format = GL_RGBA;
	}

	int width, height, nrChannels;
	unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);

	texture.Generate(width, height, data);
	stbi_image_free(data);

	return texture;
}