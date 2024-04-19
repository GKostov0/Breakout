#include "Core\Shader\Shader.h"

#include <iostream>

unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int geometryShader;

unsigned int program;

const char* geometrySource;

void CreateVertexShader(const char* source)
{
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
	geometrySource = source;
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

void CreateProgram()
{
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	if (geometrySource != NULL)
	{
		glAttachShader(program, geometryShader);
	}
	glLinkProgram(program);

	int success;
	char log[512];

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, log);
		std::cout << "[Error]: Failed to compile [--PROGRAM--]. Reason: " << log << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	if (geometryShader != NULL)
	{
		glDeleteShader(geometryShader);
	}
}

int main()
{	

	return 0;
}