#include "Player.h"

const float GRAVITY = 9.8f * 15.0f;          // Increase gravity for faster fall
const float MAX_FALL_SPEED = 100.0f * 15.0f; // Lower max fall speed for smoother landings
const float GROUND_Y = 400.0f;
const float JUMP_FORCE = -9.8f * 15.0f;      // Higher jump force for snappier jumps
const float MOVE_SPEED = 5.0f * 15.0f;

Player::Player(float x, float y, const dewcin::RGBColor& color) : position(x, y), playerColor(color) {}

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
	dewcin::Renderer::FillRectangle({ int(position.x + 0.5f), int(position.y + 0.5f), 50, 50 }, playerColor);
}