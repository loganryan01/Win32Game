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

std::string Level::GetName() const
{
	return levelName;
}