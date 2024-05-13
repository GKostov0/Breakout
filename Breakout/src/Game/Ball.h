#pragma once

#include <glad\glad.h>
#include <glm\glm.hpp>

#include "Core\GameObject\GameObject.h"
#include "Core\Texture\Texture.h"

class Ball : public GameObject
{
public:
	float radius;
	bool isStuck;

	Ball();
	Ball(glm::vec2 pos, float radius, glm::vec2 vel, Texture2D spr);

	glm::vec2 Move(float dt, unsigned int window_width);
	void Reset(glm::vec2 pos, glm::vec2 vel);
};