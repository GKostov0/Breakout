#include "ResourcesProvider.h"
#include "stb_image.h"

#include <iostream>
#include <sstream>
#include <fstream>


std::map<std::string, Shader> ResourcesProvider::Shaders;

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
