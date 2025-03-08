#include "Level.h"

Level::Level(const std::string& name) : levelName(name) {}

Level::~Level()
{
	// Destroy the level
	gameObjects.clear();
};

void Level::Load()
{
	// Load the level
}

void Level::Unload()
{
	// Unload the level
}

void Level::Update(float delta)
{
	for (auto& obj : gameObjects)
	{
		obj->Update(delta);
	}
}

void Level::Render()
{
	for (auto& obj : gameObjects)
	{
		obj->Render();
	}
}

void Level::AddGameObject(std::shared_ptr<GameObject> obj)
{
	gameObjects.push_back(obj);
}

void Level::DetectCollisions()
{
	size_t count = gameObjects.size();

	for (size_t i = 0; i < count; ++i)
	{
		for (size_t j = i + 1; j < count; ++j) 
		{
			if (gameObjects[i]->bounds.Intersects(gameObjects[j]->bounds))
			{
				// Notify both objects
				gameObjects[i]->OnCollision(gameObjects[j].get());
				gameObjects[j]->OnCollision(gameObjects[i].get());
			}
		}
	}
}

std::string Level::GetName() const
{
	return levelName;
}