#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "dewcin/renderer.h"
#include "dewcin/input.h"
#include "maths/Matrix.h"

class Player : public GameObject
{
public:
	Player(float x, float y, const dewcin::RGBColor& color, int playerId);
	void Update(float delta) override;
	void Render() override;

	void OnCollision(GameObject* other) override;

private:
	Matrix3x3 getTransformationMatrix() const;

private:
	Vector2 velocity = { 0, 0 };

	float scaleX, scaleY;
	float rotation;

	const dewcin::RGBColor& playerColor;

	bool isJumping = false;
	bool isGrounded = false;
	float groundYPos = 0;
};

#endif