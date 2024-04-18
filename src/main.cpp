#include "Core\Shader\Shader.h"

#include <iostream>

void CreateVertexShader(const char* source)
{
	unsigned int vertexShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &source, NULL);
	glCompileShader(vertexShader);

	int success;
	char log[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, log);
		std::cout << "[Error]: Failed to compile [--VERTEX--] shader. Reason: " << log << std::endl;
	}
}

void CreateFragmentShader(const char* source)
{
	unsigned int fragmentShader;

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &source, NULL);
	glCompileShader(fragmentShader);

	int success;
	char log[512];

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, log);
		std::cout << "[Error]: Failed to compile [--FRAGMENT--] shader. Reason: " << log << std::endl;
	}
}

void CreateGeometryShader(const char* source)
{
	unsigned int geometryShader;

	geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geometryShader, 1, &source, NULL);
	glCompileShader(geometryShader);

	int success;
	char log[512];

	glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(geometryShader, 512, NULL, log);
		std::cout << "[Error]: Failed to compile [--GEOMETRY--] shader. Reason: " << log << std::endl;
	}
}

int main()
{	

	return 0;
}