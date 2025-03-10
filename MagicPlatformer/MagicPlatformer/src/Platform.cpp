#include "Platform.h"

Platform::Platform(float x, float y, const dewcin::RGBColor& color, int platformId) : 
	scaleX(100.0f), scaleY(5.0f), platformColor(color)
{
	id = platformId;

	int boundsSizeX = 10 * static_cast<int>(scaleX);
	int boundsSizeY = 10 * static_cast<int>(scaleY);
	auto boundsXPos = static_cast<int>(x) - boundsSizeX / 2;
	auto boundsYPos = static_cast<int>(y) - boundsSizeY / 2;
	bounds = { boundsXPos + 5, boundsYPos + 5, boundsSizeX, boundsSizeY };

	position = { x, y };
}

void Platform::Update(float delta)
{
	// Empty
}

void Platform::Render()
{
	Matrix3x3 platformMatrix = getTransformationMatrix();

	dewcin::Renderer::FillTransformedRectangle({ 0, 0, 10, 10 }, platformMatrix, platformColor);
}

void Platform::OnCollision(GameObject* other)
{
	// Empty
}

Matrix3x3 Platform::getTransformationMatrix() const
{
	Matrix3x3 translation = Matrix3x3::translate(position.x, position.y);
	Matrix3x3 scaling = Matrix3x3::scale(scaleX, scaleY);
	Matrix3x3 rotationMatrix = Matrix3x3::rotate(0.0f);

	// Combine transformations: Scale -> Rotate -> Translate
	return translation * rotationMatrix * scaling;
}