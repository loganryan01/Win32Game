#include "dewcin.h"

int x = 250, y = 250;

void GameUpdate(float delta)
{
	std::wstring charBuffer = L"delta: " + std::to_wstring(delta) + L"\n";
	OutputDebugString(charBuffer.c_str());

	dewcin::Renderer::SetPixel(10, 10, { 0, 0, 255 });

	dewcin::Renderer::FillRectangle({ x, y, 320, 180 }, { 0, 255, 0 });

	if (dewcin::Input::IsKeyPressed(DC_UP))
		y -= 10;
	else if (dewcin::Input::IsKeyPressed(DC_DOWN))
		y += 10;

	if (dewcin::Input::IsKeyPressed(DC_LEFT))
		x -= 10;
	else if (dewcin::Input::IsKeyPressed(DC_RIGHT))
		x += 10;
}

dewcin_app_entry_point
{
	// Game int code

	dewcin::Game::setGameUpdate(GameUpdate);

	dewcin::Renderer::SetClearColor({ 200, 120, 45 });

	dewcin::Game::Start();

	// Game destroy code

	return 0;
}