#pragma once

#include <Application/Application.h>
#include <ECS/EntityManager.h>
#include <ECS/SystemManager.h>

class Game : public Application
{
	ECS::EntityManager entityManager;
	ECS::SystemManager systemManager;

	void CreateDemo();
public:
	Game();
};
