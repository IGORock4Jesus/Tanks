#include "Game.h"
#include <Application/Input.h>
#include "ECSRegistrator.h"

void Game::RegisterComponents() {
	ECSRegistrator reg;
	reg.RegisterComponents(&componentManager);
}

void Game::RegisterSystems()
{
	ECSRegistrator reg;
	reg.RegisterSystems(&systemManager);
}

void Game::CreateDemo()
{
	auto tank = entityManager.Create();
}

void Game::OnUpdate(float elapsedTime)
{
	systemManager.Update(elapsedTime);
}

Game::Game()
	: entityManager(1024)
{
	RegisterSystems();
	RegisterComponents();

	GetInput()->KeyDown.Add([this](std::wstring key) {
		if (key == L"Escape")
			this->Close();
		});

	CreateDemo();
}