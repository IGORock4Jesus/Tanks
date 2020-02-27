#pragma once

#include <ECS/ComponentManager.h>
#include <ECS/SystemManager.h>

class ECSRegistrator
{
public:
	void RegisterComponents(ECS::ComponentManager* componentManager);
	void RegisterSystems(ECS::SystemManager* systemManager);
};
