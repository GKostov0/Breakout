#include "GameLevel.h"

#include <fstream>
#include <sstream>

void GameLevel::Load(const char* filePath, unsigned int width, unsigned int height)
{
	this->bricks.clear();

	unsigned int tileCode;
	GameLevel level;

	std::string line;
	std::ifstream fileStream(filePath);

	std::vector<std::vector<unsigned int>> tileData;

	if (fileStream)
	{
		while (std::getline(fileStream, line))
		{
			std::istringstream sstream(line);
			std::vector<unsigned int> row;

			while (sstream >> tileCode)
			{
				row.push_back(tileCode);
			}
			tileData.push_back(row);
		}

		if (tileData.size() > 0)
		{
			this->Init(tileData, width, height);
		}
	}
}

void GameLevel::Draw(SpriteRenderer& renderer)
{
	for (GameObject& tile : this->bricks)
	{
		if (!tile.isDestroyed)
		{
			tile.Draw(renderer);
		}
	}
}

bool GameLevel::IsCompleted()
{
	for (GameObject& tile : this->bricks)
	{
		if (!tile.isSolid && !tile.isDestroyed)
		{
			return false;
		}
	}

	return true;
}

void GameLevel::Init(std::vector<std::vector<unsigned int>> tileData, unsigned int width, unsigned int height)
{
	unsigned int x = tileData[0].size();
	unsigned int y = tileData.size();

	float unit_width = width / static_cast<float>(x);
	float unit_height = height / y;

	for (unsigned int h = 0; h < y; h++)
	{
		for (unsigned int w = 0; w < x; w++)
		{
			glm::vec2 pos(unit_width * w, unit_height * h);
			glm::vec2 size(unit_width, unit_height);

			if (tileData[h][w] == 1)
			{
				// is it solid ?
				GameObject obj(pos, size, ResourcesProvider::GetTexture("block_solid"), glm::vec3(0.8f, 0.8f, 0.7f));
				obj.isSolid = true;
				this->bricks.push_back(obj);
			}
			else if (tileData[h][w] > 1)
			{
				// not solid
				glm::vec3 color = glm::vec3(1.0f);
				if (tileData[h][w] == 2)
				{
					color = glm::vec3(0.2f, 0.6f, 1.0f);
				}
				else if (tileData[h][w] == 3)
				{
					color = glm::vec3(0.0f, 0.7f, 0.0f);
				}
				else if (tileData[h][w] == 4)
				{
					color = glm::vec3(0.8f, 0.8f, 0.4f);
				}
				else if (tileData[h][w] == 5)
				{
					color = glm::vec3(1.0f, 0.5f, 0.0f);
				}

				this->bricks.push_back(GameObject(pos, size, ResourcesProvider::GetTexture("block"), color));
			}
		}
	}
}