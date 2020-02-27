#include <Windows.h>
#include "Game.h"

int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int) {
	Game game;
	game.Run();
	return 0;
}