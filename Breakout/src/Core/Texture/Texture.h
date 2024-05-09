#pragma once

#include <glad\glad.h>

class Texture2D
{
public:
	unsigned int ID;
	unsigned int image_width, image_height;

	unsigned int internal_format;
	unsigned int image_format;

	unsigned int wrap_s;
	unsigned int wrap_t;
	unsigned int filter_min;
	unsigned int filter_max;

	Texture2D();

	void Generate(unsigned int width, unsigned int height, unsigned char* data);

	void Bind() const;
};