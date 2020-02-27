#include "Game.h"
#include <Application/Input.h>

void Game::CreateDemo()
{
	auto tank = entityManager.Create();
}

Game::Game()
	: entityManager(1024)
{
	GetInput()->KeyDown.Add([this](std::wstring key) {
		if (key == L"Escape")
			this->Close();
		});

	CreateDemo();
}