#include "ECSRegistrator.h"

// components
#include "BoundsComponent.h"
#include "TextureComponent.h"

// systems
#include "SpriteRenderer.h"

void ECSRegistrator::RegisterComponents(ECS::ComponentManager* componentManager)
{
	componentManager->Register<BoundsComponent>(1024);
	componentManager->Register<TextureComponent>(1024);

	auto boundsID = ECS::GetComponentID<BoundsComponent>();
	auto textureID = ECS::GetComponentID<TextureComponent>();
}

void ECSRegistrator::RegisterSystems(ECS::SystemManager* systemManager)
{
	systemManager->Add(new SpriteRenderer());
}