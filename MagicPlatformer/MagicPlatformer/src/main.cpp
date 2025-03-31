#include "dewcin/dewcin.h"

/////////////////////////////////////////////////////////
// To do list:
// - Stop player from running through walls
// - Setup UI Manager for levels
// - Script to hold all the constant values
/////////////////////////////////////////////////////////

LevelManager& levelManager = LevelManager::GetInstance();
int lastFramesPerSecond = 0;

void GameUpdate(float delta)
{
	levelManager.Update(delta);
	levelManager.DetectCollisions();
	levelManager.Render();

	// FPS
	static int frames = 0;
	static float timePassed = 0.0f;

	frames++;
	timePassed += delta;

	if (timePassed >= 1.0f)
	{
		lastFramesPerSecond = frames;
		timePassed -= 1.0f;
		frames = 0;
	}

	auto s_frames = "FPS: " + std::to_string(lastFramesPerSecond);
	dewcin::Renderer::DrawTextOnBitmap(10, 1, 5, s_frames.c_str(), { 255, 255, 255 });

	std::string moveText = "'A' = MOVE LEFT";
	dewcin::Renderer::DrawTextOnBitmap(12, 20, 5, moveText.c_str(), { 255, 255, 255 });

	moveText = "'D' = MOVE RIGHT";
	dewcin::Renderer::DrawTextOnBitmap(12, 40, 5, moveText.c_str(), { 255, 255, 255 });
}

dewcin_app_entry_point
{
	// Game init code
	auto level1 = std::make_shared<Level>("Level 1");
	const dewcin::RGBColor& player1Color = { 255, 0, 0 };
	const dewcin::RGBColor& platformColor = { 0, 0, 0 };
	const dewcin::RGBColor& doorColor = { 255, 255, 255 };
	level1->AddGameObject(std::make_shared<Player>(80, 645, 5, 5, player1Color, 0));
	level1->AddGameObject(std::make_shared<Platform>(660, 695, 123, 5, platformColor, 1));
	level1->AddGameObject(std::make_shared<Platform>(635, 0, 118, 9, platformColor, -1));
	level1->AddGameObject(std::make_shared<Platform>(20, 355, 5, 72, platformColor, -1));
	level1->AddGameObject(std::make_shared<Platform>(1250, 290, 5, 59, platformColor, -1));
	level1->AddGameObject(std::make_shared<Door>(1250, 625, 5, 9, doorColor, "Level 2", 2));
	levelManager.AddLevel(level1);

	auto level2 = std::make_shared<Level>("Level 2");
	levelManager.AddLevel(level2);

	levelManager.SetCurrentLevel("Level 1");

	dewcin::Game::setGameUpdate(GameUpdate);

	dewcin::Renderer::SetClearColor({ 200, 120, 45 });

	// Game start code
	dewcin::Game::Start();

	// Game destroy code

	return 0;
}