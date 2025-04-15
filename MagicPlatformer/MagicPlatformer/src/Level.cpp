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
	
	uiManager.Render();
}

void Level::AddGameObject(std::shared_ptr<GameObject> obj)
{
	gameObjects.push_back(obj);
}

void Level::AddUIElement(std::shared_ptr<UIElement> uiElement)
{
	uiManager.AddElement(uiElement);
}

void Level::DetectCollisions()
{
	size_t count = gameObjects.size();

	for (size_t i = 0; i < count; ++i)
	{
		auto obj = gameObjects[i].get();

		if (!obj->collider) continue;

		obj->collider->previousCollisions = obj->collider->currentCollisions;
		obj->collider->currentCollisions.clear();
		
		for (size_t j = 0; j < count; ++j) 
		{
			auto other = gameObjects[j].get();
			
			if (obj == other || !other->collider) continue;

			if (obj->collider->bounds.Intersects(other->collider->bounds))
			{
				obj->collider->currentCollisions.push_back(gameObjects[j]);
				
				if (std::find(obj->collider->previousCollisions.begin(), obj->collider->previousCollisions.end(), gameObjects[j]) == obj->collider->previousCollisions.end())
				{
					obj->OnCollisionEnter(other);
				}
				else
				{
					obj->OnCollisionStay(other);
				}
			}
		}

		size_t prevCount = obj->collider->previousCollisions.size();
		for (size_t k = 0; k < prevCount; ++k)
		{
			auto prev = obj->collider->previousCollisions[k];

			if (std::find(obj->collider->currentCollisions.begin(), obj->collider->currentCollisions.end(), prev) == obj->collider->currentCollisions.end())
			{
				obj->OnCollisionExit(prev.get());
			}
		}
	}
}

std::string Level::GetName() const
{
	return levelName;
}