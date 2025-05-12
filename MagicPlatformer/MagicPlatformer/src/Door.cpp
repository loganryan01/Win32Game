#include "Door.h"

Door::Door(int xPos, int yPos, int scaleX, int scaleY, const dewcin::RGBColor& color, const std::string& nextLevel, int doorId) :
	doorColor(color), levelName(nextLevel)
{
	id = doorId;

	int boundsSizeX = 10 * scaleX;
	int boundsSizeY = 10 * scaleY;
	auto boundsXPos = xPos - boundsSizeX / 2;
	auto boundsYPos = yPos - boundsSizeY / 2;

	collider = std::make_unique<Collider>(boundsXPos + 5, boundsYPos + 5, boundsSizeX, boundsSizeY);

	position = { xPos, yPos };
	scale = { scaleX, scaleY };
}

void Door::Update(float delta)
{
	// Empty
}

void Door::Render()
{
	Matrix3x3 doorMatrix = getTransformationMatrix();

	dewcin::Renderer::FillTransformedRectangle({ 0, 0, 10, 10 }, doorMatrix, doorColor);
}

void Door::OnCollisionEnter(GameObject* other)
{
	// Player touches the door
	if (other->id == 0)
	{
		// Load the next level
		LevelManager& levelManager = LevelManager::GetInstance();
		levelManager.SetCurrentLevel(levelName);
	}
}

Matrix3x3 Door::getTransformationMatrix() const
{
	Matrix3x3 translation = Matrix3x3::translate(position.x, position.y);
	Matrix3x3 scaling = Matrix3x3::scale(scale.x, scale.y);
	Matrix3x3 rotationMatrix = Matrix3x3::rotate(0);

	// Combine transformations: Scale -> Rotate -> Translate
	return translation * rotationMatrix * scaling;
}