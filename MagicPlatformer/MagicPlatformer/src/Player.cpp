#include "Player.h"

const float GRAVITY = 9.8f * 15.0f;          // Increase gravity for faster fall
const float MAX_FALL_SPEED = 100.0f * 15.0f; // Lower max fall speed for smoother landings
const float GROUND_Y = 400.0f;
const float JUMP_FORCE = -9.8f * 15.0f;      // Higher jump force for snappier jumps

Player::Player(float x, float y, const dewcin::RGBColor& color) : posX(x), posY(y), playerColor(color) {}

void Player::Update(float delta)
{
	// Apply gravity
	velocityY += GRAVITY * delta;

	// Clamp velocity to prevent excessive falling speed
	if (velocityY > MAX_FALL_SPEED)
	{
		velocityY = MAX_FALL_SPEED;
	}
		
	// Update player's position
	posY += velocityY * delta;

	// Ground collision
	if (posY >= GROUND_Y)
	{
		posY = GROUND_Y;
		velocityY = 0; // Stop falling when on the ground
	}

	// On key press
	if (dewcin::Input::WasKeyHit(DC_SPACE) && posY == GROUND_Y)
	{
		velocityY = JUMP_FORCE;
	}
}

void Player::Render()
{
	dewcin::Renderer::FillRectangle({ int(posX + 0.5f), int(posY + 0.5f), 50, 50 }, playerColor);
}