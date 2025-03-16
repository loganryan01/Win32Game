#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "dewcin/renderer.h"
#include "dewcin/input.h"
#include "maths/Matrix.h"

class Player : public GameObject
{
public:
	Player(float xPos, float yPos, float scaleX, float scaleY, const dewcin::RGBColor& color, int playerId);
	void Update(float delta) override;
	void Render() override;

	void OnCollision(GameObject* other) override;

private:
	Matrix3x3 getTransformationMatrix() const;

private:
	const dewcin::RGBColor& playerColor;

	Vector2 velocity = { 0, 0 };

	float rotation = 0.0f;

	bool isJumping = false;
	bool isGrounded = false;
	float groundYPos = 0;
};

#endif