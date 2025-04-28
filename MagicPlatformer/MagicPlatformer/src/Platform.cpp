#include "Platform.h"

Platform::Platform(int xPos, int yPos, int scaleX, int scaleY, const dewcin::RGBColor& color, int platformId) :
	platformColor(color)
{
	id = platformId;

	int boundsSizeX = 10 * scaleX;
	int boundsSizeY = 10 * scaleY;
	auto boundsXPos = xPos - (boundsSizeX - 10) / 2;
	auto boundsYPos = yPos - (boundsSizeY - 10) / 2;

	collider = std::make_unique<Collider>(boundsXPos, boundsYPos, boundsSizeX, boundsSizeY);

	position = { xPos, yPos };
	scale = { scaleX, scaleY };
}

void Platform::Update(float delta)
{
	// Empty
}

void Platform::Render()
{
	Matrix3x3 platformMatrix = getTransformationMatrix();

	dewcin::Renderer::FillTransformedRectangle({ 0, 0, 10, 10 }, platformMatrix, platformColor);
	//dewcin::Renderer::DrawRectangle(collider->bounds, { 255, 255, 0 });
}

Matrix3x3 Platform::getTransformationMatrix() const
{
	Matrix3x3 translation = Matrix3x3::translate(position.x, position.y);
	Matrix3x3 scaling = Matrix3x3::scale(scale.x, scale.y);
	Matrix3x3 rotationMatrix = Matrix3x3::rotate(0);

	// Combine transformations: Scale -> Rotate -> Translate
	return translation * rotationMatrix * scaling;
}