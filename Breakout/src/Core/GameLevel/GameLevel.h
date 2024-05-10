#pragma once

#include <vector>

#include <glad\glad.h>
#include <glm\glm.hpp>

#include "Core\GameObject\GameObject.h"
#include "Core\SpriteRenderer\SpriteRenderer.h"
#include "Core\ResourcesProvider\ResourcesProvider.h"

class GameLevel
{
public:
	std::vector<GameObject> bricks;

	GameLevel() {}
	void Load(const char* filePath, unsigned int levelWidth, unsigned int levelHeight);
	void Draw(SpriteRenderer& renderer);

	bool IsCompleted();

private:
	void Init(std::vector<std::vector<unsigned int>> tileData, unsigned int width, unsigned int height);
};