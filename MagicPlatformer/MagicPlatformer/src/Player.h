#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "dewcin/renderer.h"
#include "dewcin/input.h"

class Player : public GameObject
{
public:
	Player(float x, float y, const dewcin::RGBColor& color);
	void Update(float delta) override;
	void Render() override;

private:
	float posX, posY;

	const dewcin::RGBColor& playerColor;

	float velocityY = 0.0f; // Player's vertical velocity
	bool isJumping = false;
};

#endif