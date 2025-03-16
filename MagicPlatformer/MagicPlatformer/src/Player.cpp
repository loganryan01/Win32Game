#include "Player.h"

const float GRAVITY = 9.8f * 15.0f;          // Increase gravity for faster fall
const float MAX_FALL_SPEED = 100.0f * 15.0f; // Lower max fall speed for smoother landings
const float JUMP_FORCE = -9.8f * 15.0f;      // Higher jump force for snappier jumps
const float MOVE_SPEED = 5.0f * 15.0f;

Player::Player(float xPos, float yPos, float scaleX, float scaleY, const dewcin::RGBColor& color, int playerId) :
	playerColor(color), rotation(0.0f)
{
	id = playerId;

	int boundsSizeX = 10 * static_cast<int>(scaleX);
	int boundsSizeY = 10 * static_cast<int>(scaleY);
	auto boundsXPos = static_cast<int>(xPos) - boundsSizeX / 2;
	auto boundsYPos = static_cast<int>(yPos) - boundsSizeY / 2;
	bounds = { boundsXPos + 5, boundsYPos + 5, boundsSizeX, boundsSizeY };

	position = { xPos, yPos };
	scale = { scaleX, scaleY };
}

void Player::Update(float delta)
{
	// Apply gravity
	velocity.y += GRAVITY * delta;

	// Clamp velocity to prevent excessive falling speed
	if (velocity.y > MAX_FALL_SPEED)
	{
		velocity.y = MAX_FALL_SPEED;
	}

	if (isGrounded)
	{
		position.y = groundYPos - 10.0f * scale.y;
		velocity.y = 0; // Stop falling when on the ground
	}
		
	// Update player's position
	position = position + velocity * delta;

	// On key press
	if (dewcin::Input::IsKeyPressed(DC_SPACE) && isGrounded)
	{
		isGrounded = false;
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

	int boundsSizeX = 10 * static_cast<int>(scale.x);
	int boundsSizeY = 10 * static_cast<int>(scale.y);
	auto boundsXPos = static_cast<int>(position.x) - boundsSizeX / 2;
	auto boundsYPos = static_cast<int>(position.y) - boundsSizeY / 2;
	bounds = { boundsXPos + 5, boundsYPos + 5, boundsSizeX, boundsSizeY };
	isGrounded = false;
}

void Player::Render()
{
	Matrix3x3 playerMatrix = getTransformationMatrix();
	
	dewcin::Renderer::FillTransformedRectangle({ 0, 0, 10, 10 }, playerMatrix, playerColor);
}

void Player::OnCollision(GameObject* other)
{
	// Ground collision
	if (other->id == 1)
	{
		isGrounded = true;
		groundYPos = other->position.y;
	}
}

Matrix3x3 Player::getTransformationMatrix() const
{
	Matrix3x3 translation = Matrix3x3::translate(position.x, position.y);
	Matrix3x3 scaling = Matrix3x3::scale(scale.x, scale.y);
	Matrix3x3 rotationMatrix = Matrix3x3::rotate(rotation);

	// Combine transformations: Scale -> Rotate -> Translate
	return translation * rotationMatrix * scaling;
}