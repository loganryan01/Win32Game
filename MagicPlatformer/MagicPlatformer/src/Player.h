#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "dewcin/renderer.h"
#include "dewcin/input.h"
#include "maths/Matrix.h"

class Player : public GameObject
{
public:
	Player(int xPos, int yPos, int scaleX, int scaleY, const dewcin::RGBColor& color, int playerId);
	void Update(float delta) override;
	void Render() override;

	void OnCollision(GameObject* other) override;

private:
	Matrix3x3 getTransformationMatrix() const;

private:
	const dewcin::RGBColor& playerColor;

	Vector2 velocity = { 0, 0 };

	int rotation = 0;

	bool isJumping = false;
	bool isGrounded = false;
	int groundYPos = 0;
};

#endif