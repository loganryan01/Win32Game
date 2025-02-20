#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <memory>
#include "GameObject.h"

class Level
{
public:
	explicit Level(const std::string& name);
	~Level();

	void Load();
	void Unload();
	void Update(float delta);
	void Render();

	void AddGameObject(std::shared_ptr<GameObject> obj);

	std::string GetName() const;

private:
	std::string levelName;
	std::vector<std::shared_ptr<GameObject>> gameObjects;
};

#endif