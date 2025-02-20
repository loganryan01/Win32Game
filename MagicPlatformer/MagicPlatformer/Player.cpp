#include "Player.h"

Player::Player(int x, int y, const dewcin::RGBColor& color) : posX(x), posY(y), playerColor(color) {}

void Player::Update(float delta)
{
	// Player logic
}

void Player::Render()
{
	dewcin::Renderer::FillRectangle({ posX, posY, 50, 50 }, playerColor);
}