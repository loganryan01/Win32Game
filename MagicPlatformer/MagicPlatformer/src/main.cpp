#include "dewcin/dewcin.h"
#include "Defs.h"

/////////////////////////////////////////////////////////
// To do list:
// - Create Room 3 (Prize Room)
// - Create destructor for UI Manager
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
	level1->AddGameObject(std::make_shared<Platform>(635, 690, 128, 5, BLACK, 1)); // Floor
	level1->AddGameObject(std::make_shared<Platform>(20, 355, 5, 72, BLACK, 3)); // Wall
	level1->AddGameObject(std::make_shared<Platform>(1250, 285, 5, 58, BLACK, 3)); // Wall
	level1->AddGameObject(std::make_shared<Platform>(635, 20, 118, 5, BLACK, 3)); // Roof
	level1->AddGameObject(std::make_shared<Door>(1250, 620, 5, 9, WHITE, LEVEL_TWO_NAME, 2));

	level1->AddUIElement(std::make_shared<UIText>(12, 20, 5, MOVE_LEFT_TEXT.c_str(), WHITE));
	level1->AddUIElement(std::make_shared<UIText>(12, 40, 5, MOVE_RIGHT_TEXT.c_str(), WHITE));
	levelManager.AddLevel(level1);

	auto level2 = std::make_shared<Level>(LEVEL_TWO_NAME);
	level2->AddGameObject(std::make_shared<Player>(80, 645, 5, 5, RED, 0));
	level2->AddGameObject(std::make_shared<Platform>(220, 690, 46, 5, BLACK, 1)); // Floor
	level2->AddGameObject(std::make_shared<Platform>(635, 620, 28, 5, BLACK, 1)); // Platform
	level2->AddGameObject(std::make_shared<Platform>(1050, 690, 46, 5, BLACK, 1)); // Floor
	level2->AddGameObject(std::make_shared<Platform>(20, 285, 5, 58, BLACK, 3)); // Wall
	level2->AddGameObject(std::make_shared<Platform>(1250, 285, 5, 58, BLACK, 3)); // Wall
	level2->AddGameObject(std::make_shared<Platform>(635, 20, 118, 5, BLACK, 3)); // Roof
	level2->AddGameObject(std::make_shared<Door>(20, 620, 5, 9, WHITE, LEVEL_ONE_NAME, 2));
	level2->AddGameObject(std::make_shared<Door>(1250, 620, 5, 9, WHITE, LEVEL_THREE_NAME, 2));

	level2->AddUIElement(std::make_shared<UIText>(12, 20, 5, JUMP_TEXT.c_str(), WHITE));
	levelManager.AddLevel(level2);

	auto level3 = std::make_shared<Level>(LEVEL_THREE_NAME);
	level3->AddGameObject(std::make_shared<Player>(80, 645, 5, 5, RED, 0));
	level3->AddGameObject(std::make_shared<Platform>(635, 690, 128, 5, BLACK, 1)); // Floor
	level3->AddGameObject(std::make_shared<Platform>(1250, 355, 5, 72, BLACK, 3)); // Wall
	level3->AddGameObject(std::make_shared<Platform>(20, 285, 5, 58, BLACK, 3)); // Wall
	level3->AddGameObject(std::make_shared<Platform>(635, 20, 118, 5, BLACK, 3)); // Roof
	level3->AddGameObject(std::make_shared<Door>(20, 620, 5, 9, WHITE, LEVEL_TWO_NAME, 2));
	level3->AddGameObject(std::make_shared<Collectable>(1140, 620, 5, 5, GREEN, 2));

	levelManager.AddLevel(level3);

	levelManager.SetCurrentLevel(LEVEL_THREE_NAME);

	dewcin::Game::setGameUpdate(GameUpdate);

	dewcin::Renderer::SetClearColor({ 200, 120, 45 });

	// Game start code
	dewcin::Game::Start();

	// Game destroy code

	return 0;
}