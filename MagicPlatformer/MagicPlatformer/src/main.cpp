#include "dewcin/dewcin.h"

LevelManager& levelManager = LevelManager::GetInstance();

void GameUpdate(float delta)
{
	// FPS
	static int frames = 0;
	static float timePassed = 0.0f;

	frames++;
	timePassed += delta;

	if (timePassed >= 1.0f)
	{
		std::wstring charBuffer = L"FPS: " + std::to_wstring(frames / 10) + L"\n";
		OutputDebugString(charBuffer.c_str());

		timePassed -= 1.0f;
		frames = 0;
	}

	levelManager.Update(delta);
	levelManager.DetectCollisions();
	levelManager.Render();
}

dewcin_app_entry_point
{
	// Game init code
	auto level1 = std::make_shared<Level>("Level 1");
	const dewcin::RGBColor& player1Color = { 255, 0, 0 };
	const dewcin::RGBColor& platformColor = { 0, 0, 0 };
	level1->AddGameObject(std::make_shared<Player>(100, 100, player1Color, 0));
	level1->AddGameObject(std::make_shared<Platform>(100, 500, platformColor, 1));
	levelManager.AddLevel(level1);

	levelManager.SetCurrentLevel("Level 1");

	dewcin::Game::setGameUpdate(GameUpdate);

	dewcin::Renderer::SetClearColor({ 200, 120, 45 });

	// Game start code
	dewcin::Game::Start();

	// Game destroy code

	return 0;
}