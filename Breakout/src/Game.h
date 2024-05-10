#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "Core\GameLevel\GameLevel.h"

enum GameState
{
	GAME_ACTIVE = 0,
	GAME_MENNU = 1,
	GAME_WIN = 2
};

const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
const float PLAYER_VELOCITY(500.0f);

class Game
{
public:
	GameState state;

	bool keys[1024];
	unsigned int width, height;
	std::vector<GameLevel> levels;

	unsigned int level;

	Game(unsigned int width, unsigned int height);
	~Game();

	void Init();

	void ProcessInput(float dt);
	void Update();
	void Render();
};