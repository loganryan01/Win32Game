#include "dewcin.h"

void GameUpdate(float delta)
{
	std::wstring charBuffer = L"delta: " + std::to_wstring(delta) + L"\n";
	OutputDebugString(charBuffer.c_str());
}

dewcin_app_entry_point
{
	// Game int code

	dewcin::Game::setGameUpdate(GameUpdate);

	dewcin::Game::Start();

	// Game destroy code

	return 0;
}