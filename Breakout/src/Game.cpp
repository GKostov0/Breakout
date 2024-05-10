#include "Game.h"

#include "Core\ResourcesProvider\ResourcesProvider.h"
#include "Core\SpriteRenderer\SpriteRenderer.h"
#include "Core\GameObject\GameObject.h"

SpriteRenderer* renderer;
GameObject* player;

Game::Game(unsigned int width, unsigned int height)
	: state(GAME_ACTIVE), keys(), width(width), height(height)
{

}

Game::~Game()
{
	delete renderer;
	delete player;
}

void Game::Init()
{
	ResourcesProvider::LoadShader("src//shaders//vertex.vs", "src//shaders//fragment.frag", nullptr, "sprite");

	glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(this->width), static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);

	ResourcesProvider::GetShader("sprite").Use().SetInteger("img", 0);
	ResourcesProvider::GetShader("sprite").SetMatrix4("proj", proj);

	renderer = new SpriteRenderer(ResourcesProvider::GetShader("sprite"));

	ResourcesProvider::LoadTexture("background.jpg", false, "background");
}