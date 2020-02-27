#include "..\Game\Game.h"
#include "Game.h"
#include "LevelConstructor.h"
#include "ResourceManager.h"
#include "ECS.h"
#include "BoundsComponent.h"
#include "Block.h"

namespace Game
{
void RegisterComponents() {
	ECS::Register<Bounds>();
	ECS::Register<Block>();
}

void RegisterSystems()
{
}

void Initialize() {
	RegisterComponents();

	LevelConstructor::Construct(ResourceManager::GetLevel(L"28"));
}
}