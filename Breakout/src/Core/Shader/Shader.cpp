#include "Shader.h"

Shader& Shader::Use()
{
	glUseProgram(this->ID);
	return *this;
}

void Shader::Compile(const char* vertex, const char* fragment, const char* geometry)
{
	unsigned int v, f, g;

	v = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(v, 1, &vertex, NULL);
	glCompileShader(v);

	CheckCompileStatus(v, ShaderCompileType::Vertex);

	f = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(f, 1, &fragment, NULL);
	glCompileShader(f);

	CheckCompileStatus(f, ShaderCompileType::Fragment);

	if (geometry != nullptr)
	{
		g = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(g, 1, &geometry, NULL);
		glCompileShader(g);

		CheckCompileStatus(g, ShaderCompileType::Geometry);
	}

	ID = glCreateProgram();
	glAttachShader(ID, v);
	glAttachShader(ID, f);
	if (geometry != NULL)
	{
		glAttachShader(ID, g);
	}
	glLinkProgram(ID);

	CheckCompileStatus(ID, ShaderCompileType::Program);

	glDeleteShader(v);
	glDeleteShader(f);
	if (geometry != nullptr)
	{
		glDeleteShader(g);
	}
}

void Shader::CheckCompileStatus(unsigned int object, ShaderCompileType type)
{
	int success;
	char log[512];

	if (type != ShaderCompileType::Program)
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(object, 512, NULL, log);
			std::cout << "[Error]: Failed to compile [--" << type << "--] shader.Reason:\n" << log << std::endl;
		}
	}
	else
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(object, 512, NULL, log);
			std::cout << "[Error]: Failed to compile [--" << type << "--].Reason: " << log << std::endl;
		}
	}
}

void Shader::SetMatrix4(const char* name, const glm::mat4& matrix, bool useShader)
{
	if (useShader)
	{
		this->Use();
	}
	glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, false, glm::value_ptr(matrix));
}

void Shader::SetVector3f(const char* name, float x, float y, float z, bool useShader)
{
	if (useShader)
	{
		this->Use();
	}

	glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}

void Shader::SetVector3f(const char* name, glm::vec3& value, bool useShader)
{
	if (useShader)
	{
		this->Use();
	}

	glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}