#include "LevelManager.h"

LevelManager& LevelManager::GetInstance()
{
	static LevelManager instance;
	return instance;
}

LevelManager::LevelManager() = default;

void LevelManager::AddLevel(std::shared_ptr<Level> level)
{
	levels.push_back(level);
	if (!currentLevel)
	{
		currentLevel = level; // Set the first added level as current
	}
}

void LevelManager::SetCurrentLevel(const std::string& name)
{
	for (auto& level : levels)
	{
		if (level->GetName() == name)
		{
			if (currentLevel && currentLevel->GetName() != name)
			{
				currentLevel->Unload(); // Only unload if switching levels
			}

			currentLevel = level;

			// Load the level and its game objects if not already loaded
			currentLevel->Load();
			return;
		}
	}
}

void LevelManager::Update(float delta)
{
	if (currentLevel)
	{
		currentLevel->Update(delta);
	}
}

void LevelManager::Render()
{
	if (currentLevel)
	{
		currentLevel->Render();
	}
}