#include "Ball.h"

Ball::Ball()
	: GameObject(), radius(12.5f), isStuck(true) 
{

}

Ball::Ball(glm::vec2 pos, float radius, glm::vec2 vel, Texture2D spr)
	: GameObject(pos, glm::vec2(radius * 2.0f, radius * 2.0f), spr, glm::vec3(1.0f), vel), radius(radius), isStuck(true)
{

}

glm::vec2 Ball::Move(float dt, unsigned int window_width)
{
	if (!this->isStuck)
	{
		this->position += this->velocity * dt;

		if (this->position.x <= 0.0f)
		{
			this->velocity.x = -this->velocity.x;
			this->position.x = 0.0f;
		}
		else if (this->position.x + this->size.x >= window_width)
		{
			this->velocity.x = -this->velocity.x;
			this->position.x = window_width - this->size.x;
		}

		if (this->position.y <= 0.0f)
		{
			this->velocity.y = -this->velocity.y;
			this->position.y = 0.0f;
		}
	}

	return this->position;
}

void Ball::Reset(glm::vec2 pos, glm::vec2 vel)
{
	this->position = pos;
	this->velocity = vel;
	this->isStuck = true;
}