#include "Player.h"

const int GRAVITY = 1;          // Increase gravity for faster fall
const int MAX_FALL_SPEED = 7; // Lower max fall speed for smoother landings
const int JUMP_FORCE = -23;      // Higher jump force for snappier jumps
const int MOVE_SPEED = 1;

Player::Player(int xPos, int yPos, int scaleX, int scaleY, const dewcin::RGBColor& color, int playerId) :
	playerColor(color), rotation(0)
{
	id = playerId;

	int boundsSizeX = 10 * scaleX;
	int boundsSizeY = 10 * scaleY;
	auto boundsXPos = xPos - boundsSizeX / 2;
	auto boundsYPos = yPos - boundsSizeY / 2;
	bounds = { xPos, yPos, boundsSizeX, boundsSizeY };

	position = { xPos, yPos };
	scale = { scaleX, scaleY };
}

void Player::Update(float delta)
{
	// Apply gravity
	if (!isGrounded)
	{
		velocity.y += GRAVITY;

		// Clamp velocity to prevent excessive falling speed
		if (velocity.y > MAX_FALL_SPEED)
		{
			velocity.y = MAX_FALL_SPEED;
		}
	}
	else
	{
		position.y = groundYPos - 10 * scale.y;
		velocity.y = 0; // Stop falling when on the ground
	}
		
	// Update player's position
	position = position + velocity;

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

	// Updated collider box position
	auto boundsXPos = position.x - (bounds.width - 10) / 2;
	auto boundsYPos = position.y - (bounds.height - 10) / 2;
	bounds.x = boundsXPos;
	bounds.y = boundsYPos;
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