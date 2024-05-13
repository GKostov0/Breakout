#include "Game.h"

#include "Core\ResourcesProvider\ResourcesProvider.h"
#include "Core\SpriteRenderer\SpriteRenderer.h"

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

bool Game::CheckCollision(Ball& ball, GameObject& other)
{
	glm::vec2 center(ball.position + ball.radius);

	glm::vec2 aabb_half_extends(other.size.x / 2.0f, other.size.y / 2.0f);
	glm::vec2 aabb_center(other.position.x + aabb_half_extends.x, other.position.y + aabb_half_extends.y);

	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extends, aabb_half_extends);

	glm::vec2 closest = aabb_center + clamped;

	difference = closest - center;

	// Boxy collision - simple...
	//bool CollisionX = (ball.position.x + ball.size.x >= other.position.x) && (other.position.x + other.size.x >= ball.position.x);
	//bool CollisionY = (ball.position.y + ball.size.y >= other.position.y) && (other.position.y + other.size.y >= ball.position.y);

	//return CollisionX && CollisionY;

	// Circular collision - not so simple...
	return glm::length(difference) < ball.radius;
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