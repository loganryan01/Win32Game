#include "dewcin.h"

float x = 250, y = 250;

void GameUpdate(float delta)
{
	static int frames = 0;
	static float timePassed = 0.0f;

	frames++;
	timePassed += delta;

	if (timePassed >= 1.0f)
	{
		std::wstring charBuffer = L"delta: " + std::to_wstring(delta) + L"\n";
		OutputDebugString(charBuffer.c_str());

		timePassed -= 1.0f;
		frames = 0;
	}

	dewcin::Renderer::SetPixel(10, 10, { 0, 0, 255 });
	
	dewcin::Renderer::FillRectangle({ int(x + 0.5f), int(y + 0.5f), 320, 180 }, { 0, 255, 0 });

	if (dewcin::Input::IsKeyPressed(DC_W))
		y -= 100.0f * delta;
	else if (dewcin::Input::IsKeyPressed(DC_S))
		y += 100.0f * delta;

	if (dewcin::Input::IsKeyPressed(DC_A))
		x -= 100.0f * delta;
	else if (dewcin::Input::IsKeyPressed(DC_D))
		x += 100.0f * delta;
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