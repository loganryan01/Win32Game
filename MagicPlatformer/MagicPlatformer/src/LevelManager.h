#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <vector>
#include <memory>
#include "Level.h"

class LevelManager
{
public:
	static LevelManager& GetInstance();

	void AddLevel(std::shared_ptr<Level> level);
	void SetCurrentLevel(const std::string& name);
	void Update(float delta);
	void Render();

private:
	LevelManager();
	~LevelManager() = default;

	std::vector<std::shared_ptr<Level>> levels;
	std::shared_ptr<Level> currentLevel;
};

#endif LEVELMANGER_H