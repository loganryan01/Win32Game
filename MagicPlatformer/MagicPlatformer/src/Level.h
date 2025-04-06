#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <memory>
#include "GameObject.h"
#include "UIManager.h"

class Level
{
public:
	explicit Level(const std::string& name);
	~Level();

	void Load();
	void Unload();
	void Update(float delta);
	void Render();
	void DetectCollisions();

	void AddGameObject(std::shared_ptr<GameObject> obj);
	void AddUIElement(std::shared_ptr<UIElement> uiElement);

	std::string GetName() const;

private:
	std::string levelName;
	std::vector<std::shared_ptr<GameObject>> gameObjects;

	UIManager uiManager;
};

#endif