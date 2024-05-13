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

	ResourcesProvider::LoadTexture("src//Sprites//background.jpg", false, "background");
	ResourcesProvider::LoadTexture("src//Sprites//ball.png", true, "ball");
	ResourcesProvider::LoadTexture("src//Sprites//block.png", false, "block");
	ResourcesProvider::LoadTexture("src//Sprites//block_solid.png", false, "block_solid");
	ResourcesProvider::LoadTexture("src//Sprites//paddle.png", true, "paddle");

	GameLevel one, two, three, four;

	one.Load("src//levels//one.lvl", this->width, this->height / 2);
	two.Load("src//levels//two.lvl", this->width, this->height / 2);
	three.Load("src//levels//three.lvl", this->width, this->height / 2);
	four.Load("src//levels//four.lvl", this->width, this->height / 2);

	this->levels.push_back(one);
	this->levels.push_back(two);
	this->levels.push_back(three);
	this->levels.push_back(four);

	this->level = 0;

	glm::vec2 playerPos = glm::vec2(this->width / 2.0f - PLAYER_SIZE.x / 2, this->height - PLAYER_SIZE.y);
	player = new GameObject(playerPos, PLAYER_SIZE, ResourcesProvider::GetTexture("paddle"));
}

void Game::Update(float dt)
{

}

void Game::ProcessInput(float dt)
{
	if (this->state == GAME_ACTIVE)
	{
		float velocity = PLAYER_VELOCITY * dt;

		if (this->keys[GLFW_KEY_A])
		{
			if (player->position.x >= 0.0f)
			{
				player->position.x -= velocity;
			}
		}
		if (this->keys[GLFW_KEY_D])
		{
			if (player->position.x <= this->width - player->size.x)
			{
				player->position.x += velocity;
			}
		}
	}
}

void Game::Render()
{
	if (this->state == GAME_ACTIVE)
	{
		renderer->DrawSprite(ResourcesProvider::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(this->width, this->height), 0.0f);

		this->levels[this->level].Draw(*renderer);

		player->Draw(*renderer);
	}
}