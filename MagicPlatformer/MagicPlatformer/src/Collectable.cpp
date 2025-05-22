#include "Collectable.h"
#include "dewcin/game.h"

Collectable::Collectable(int xPos, int yPos, int scaleX, int scaleY, const dewcin::RGBColor& color, int collectableId) :
	collectableColor(color)
{
	id = collectableId;

	int boundsSizeX = 10 * scaleX;
	int boundsSizeY = 10 * scaleY;
	auto boundsXPos = xPos - boundsSizeX / 2;
	auto boundsYPos = yPos - boundsSizeY / 2;

	collider = std::make_unique<Collider>(boundsXPos + 5, boundsYPos + 5, boundsSizeX, boundsSizeY);

	position = { xPos, yPos };
	scale = { scaleX, scaleY };
}

void Collectable::Update(float delta)
{
	// Empty
}

void Collectable::Render()
{
	Matrix3x3 collectableMatrix = getTransformationMatrix();

	dewcin::Renderer::FillTransformedRectangle({ 0, 0, 10, 10 }, collectableMatrix, collectableColor);
}

void Collectable::OnCollisionEnter(GameObject* other)
{
	// Player touches the collectable
	if (other->id == 0)
	{
		// Close the game
		dewcin::Game::Stop();
	}
}

Matrix3x3 Collectable::getTransformationMatrix() const
{
	Matrix3x3 translation = Matrix3x3::translate(position.x, position.y);
	Matrix3x3 scaling = Matrix3x3::scale(scale.x, scale.y);
	Matrix3x3 rotationMatrix = Matrix3x3::rotate(0);

	// Combine transformations: Scale -> Rotate -> Translate
	return translation * rotationMatrix * scaling;
}
