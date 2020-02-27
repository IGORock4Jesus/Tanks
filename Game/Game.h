#pragma once

#include <Application/Application.h>
#include <ECS/EntityManager.h>
#include <ECS/SystemManager.h>
#include <ECS/ComponentManager.h>

class Game : public Application
{
	ECS::EntityManager entityManager;
	ECS::SystemManager systemManager;
	ECS::ComponentManager componentManager;

	void RegisterComponents();
	void RegisterSystems();

	void CreateDemo();

	virtual void OnUpdate(float elapsedTime)override;
public:
	Game();
};
