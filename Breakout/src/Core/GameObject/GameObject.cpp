#include "GameObject.h"

GameObject::GameObject()
	: position(0.0f, 0.0f), size(1.0f, 1.0f), velocity(0.0f), color(1.0f), rotation(0.0f), sprite(), isSolid(false), isDestroyed(false)
{

}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D spr, glm::vec3 color, glm::vec2 vel)
	: position(pos), size(size), velocity(vel), color(color), rotation(0.0f), sprite(spr), isSolid(false), isDestroyed(false)
{

}

void GameObject::Draw(SpriteRenderer& renderer)
{
	renderer.DrawSprite(this->sprite, this->position, this->size, this->rotation, this->color);
}