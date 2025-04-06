#include "dewcin/dewcin.h"
#include "Defs.h"

/////////////////////////////////////////////////////////
// To do list:
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
	dewcin::Renderer::DrawTextOnBitmap(10, 1, 5, s_frames.c_str(), WHITE);
}

dewcin_app_entry_point
{
	// Game init code
	auto level1 = std::make_shared<Level>(LEVEL_ONE_NAME);
	level1->AddGameObject(std::make_shared<Player>(80, 645, 5, 5, RED, 0));
	level1->AddGameObject(std::make_shared<Platform>(660, 695, 123, 5, BLACK, 1));
	level1->AddGameObject(std::make_shared<Platform>(635, 0, 118, 9, BLACK, 3));
	level1->AddGameObject(std::make_shared<Platform>(20, 355, 5, 72, BLACK, 3));
	level1->AddGameObject(std::make_shared<Platform>(1250, 290, 5, 59, BLACK, 3));
	level1->AddGameObject(std::make_shared<Door>(1250, 625, 5, 9, WHITE, LEVEL_TWO_NAME, 2));

	level1->AddUIElement(std::make_shared<UIText>(12, 20, 5, MOVE_LEFT_TEXT.c_str(), WHITE));
	level1->AddUIElement(std::make_shared<UIText>(12, 40, 5, MOVE_RIGHT_TEXT.c_str(), WHITE));
	levelManager.AddLevel(level1);

	auto level2 = std::make_shared<Level>(LEVEL_TWO_NAME);
	levelManager.AddLevel(level2);

	levelManager.SetCurrentLevel(LEVEL_ONE_NAME);

	dewcin::Game::setGameUpdate(GameUpdate);

	dewcin::Renderer::SetClearColor({ 200, 120, 45 });

	// Game start code
	dewcin::Game::Start();

	// Game destroy code

	return 0;
}