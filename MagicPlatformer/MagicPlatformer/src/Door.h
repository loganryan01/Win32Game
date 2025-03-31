#ifndef DOOR_H
#define DOOR_H
#include "GameObject.h"
#include "LevelManager.h"

#include <string>

class Door : public GameObject
{
public:
	Door(int xPos, int yPos, int scaleX, int scaleY, const dewcin::RGBColor& color, const std::string nextLevel, int doorId);
	void Update(float delta) override;
	void Render() override;

	void OnCollision(GameObject* other) override;

private:
	Matrix3x3 getTransformationMatrix() const;

private:
	const dewcin::RGBColor& doorColor;
	const std::string levelName;
};

#endif