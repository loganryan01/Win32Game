#include "Player.h"
#include <string>
#include <memory>
#include <algorithm>

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

	collider = std::make_unique<Collider>(xPos, yPos, boundsSizeX, boundsSizeY);

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
		
	// Update player's position
	position = position + velocity;

	// On key press
	if (dewcin::Input::IsKeyPressed(DC_SPACE) && isGrounded)
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

	// Updated collider box position
	auto boundsXPos = position.x - (collider->bounds.width - 10) / 2;
	auto boundsYPos = position.y - (collider->bounds.height - 10) / 2;
	collider->UpdatePosition(boundsXPos, boundsYPos);
}

void Player::Render()
{
	Matrix3x3 playerMatrix = getTransformationMatrix();
	
	dewcin::Renderer::FillTransformedRectangle({ 0, 0, 10, 10 }, playerMatrix, playerColor);
	//dewcin::Renderer::DrawRectangle(collider.get()->bounds, { 0, 255, 0 });
}

void Player::OnCollisionEnter(GameObject* other)
{
	if (other->id == 1 && velocity.y > 0)
	{
		isGrounded = true;
		position.y = other->collider.get()->bounds.GetTop() - ((collider.get()->bounds.height / 2) + 4);
		velocity.y = 0; // Stop falling when on the ground
	}

	if (other->id == 3)
	{
		auto a = collider.get()->bounds;
		const auto& b = other->collider.get()->bounds;

		int xOverlap = std::min(a.GetRight(), b.GetRight()) - std::min(a.GetLeft(), b.GetLeft());
		int yOverlap = std::min(a.GetBottom(), b.GetBottom()) - std::min(a.GetTop(), b.GetTop());

		if (xOverlap > 0 && yOverlap > 0)
		{
			if (xOverlap < yOverlap)
			{
				// Horizontal Collision (wall)
				if ((a.GetLeft() + a.width / 2) < (b.GetLeft() + b.width / 2))
				{
					position.x -= 1;
				}
				else
				{
					position.x += 1;
				}

				velocity.x = 0;
			}
		}
	}
}

void Player::OnCollisionStay(GameObject* other)
{
	// Empty
}

void Player::OnCollisionExit(GameObject* other)
{
	if (other->id == 1)
	{
		isGrounded = false;
	}

	if (other->id == 3)
	{
		auto a = collider.get()->bounds;
		const auto& b = other->collider.get()->bounds;

		int xOverlap = std::min(a.GetRight(), b.GetRight()) - std::min(a.GetLeft(), b.GetLeft());
		int yOverlap = std::min(a.GetBottom(), b.GetBottom()) - std::min(a.GetTop(), b.GetTop());

		if (xOverlap > 0 && yOverlap > 0)
		{
			if (!(xOverlap < yOverlap))
			{
				isGrounded = false;
			}
		}
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