#include "Player.h"
#include <string>

const float GRAVITY = 9.8f * 15.0f;          // Increase gravity for faster fall
const float MAX_FALL_SPEED = 100.0f * 15.0f; // Lower max fall speed for smoother landings
const float GROUND_Y = 400.0f;
const float JUMP_FORCE = -9.8f * 15.0f;      // Higher jump force for snappier jumps
const float MOVE_SPEED = 5.0f * 15.0f;

Player::Player(float x, float y, const dewcin::RGBColor& color) : position(x, y), scaleX(2.0f), scaleY(1.0f), rotation(0.0f), playerColor(color) {}

void Player::Update(float delta)
{
	// Apply gravity
	velocity.y += GRAVITY * delta;

	// Clamp velocity to prevent excessive falling speed
	if (velocity.y > MAX_FALL_SPEED)
	{
		velocity.y = MAX_FALL_SPEED;
	}
		
	// Update player's position
	position = position + velocity * delta;

	// Ground collision
	if (position.y >= GROUND_Y)
	{
		position.y = GROUND_Y;
		velocity.y = 0; // Stop falling when on the ground
	}

	// On key press
	if (dewcin::Input::WasKeyHit(DC_SPACE) && position.y == GROUND_Y)
	{
		velocity.y = JUMP_FORCE;
	}

	if (dewcin::Input::IsKeyPressed(DC_D))
	{
		velocity.x = MOVE_SPEED;
	}
	else if (dewcin::Input::IsKeyPressed(DC_A))
	{
		velocity.x = -MOVE_SPEED;
	}
	else
	{
		velocity.x = 0;
	}
}

void Player::Render()
{
	Matrix3x3 playerMatrix = getTransformationMatrix();
	
	dewcin::Renderer::FillTransformedRectangle({ 0, 0, 50, 50 }, playerMatrix, playerColor);
}

Matrix3x3 Player::getTransformationMatrix() const
{
	Matrix3x3 translation = Matrix3x3::translate(position.x, position.y);
	Matrix3x3 scaling = Matrix3x3::scale(scaleX, scaleY);
	Matrix3x3 rotationMatrix = Matrix3x3::rotate(rotation);

	// Combine transformations: Scale -> Rotate -> Translate
	return translation * rotationMatrix * scaling;
}