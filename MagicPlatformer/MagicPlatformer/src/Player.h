#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "dewcin/renderer.h"
#include "dewcin/input.h"
#include "maths/Vector.h"

class Player : public GameObject
{
public:
	Player(float x, float y, const dewcin::RGBColor& color);
	void Update(float delta) override;
	void Render() override;

private:
	Vector2 position;
	Vector2 velocity = { 0, 0 };

	const dewcin::RGBColor& playerColor;

	bool isJumping = false;
};

#endif