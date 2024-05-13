#include "Game.h"

#include "Core\ResourcesProvider\ResourcesProvider.h"
#include "Core\SpriteRenderer\SpriteRenderer.h"
#include "Game\Ball.h"

SpriteRenderer* renderer;
GameObject* player;
Ball* ball;

const glm::vec2 INITAIL_BALL_VELOCITY(100.0f, -350.0f);
const float BALL_RADIUS = 12.5f;

Game::Game(unsigned int width, unsigned int height)
	: state(GAME_ACTIVE), keys(), width(width), height(height), level(0)
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
	glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);

	player = new GameObject(playerPos, PLAYER_SIZE, ResourcesProvider::GetTexture("paddle"));
	ball = new Ball(ballPos, BALL_RADIUS, INITAIL_BALL_VELOCITY, ResourcesProvider::GetTexture("ball"));
}

void Game::Update(float dt)
{
	ball->Move(dt, this->width);
	this->DoCollisions();
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
				if (ball->isStuck)
				{
					ball->position.x -= velocity;
				}
			}
		}
		if (this->keys[GLFW_KEY_D])
		{
			if (player->position.x <= this->width - player->size.x)
			{
				player->position.x += velocity;
				if (ball->isStuck)
				{
					ball->position.x += velocity;
				}
			}
		}
		if (this->keys[GLFW_KEY_SPACE])
		{
			ball->isStuck = false;
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

		ball->Draw(*renderer);
	}
}

bool Game::CheckCollision(GameObject& first, GameObject& second)
{
	bool CollisionX = (first.position.x + first.size.x >= second.position.x) && (second.position.x + second.size.x >= first.position.x);
	bool CollisionY = (first.position.y + first.size.y >= second.position.y) && (second.position.y + second.size.y >= first.position.y);

	return CollisionX && CollisionY;
}

void Game::DoCollisions()
{
	for (GameObject& box : this->levels[this->level].bricks)
	{
		if (!box.isDestroyed)
		{
			if (CheckCollision(*ball, box))
			{
				if (!box.isSolid)
				{
					box.isDestroyed = true;
				}
			}
		}
	}
}