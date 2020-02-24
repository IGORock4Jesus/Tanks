#include "ConcreteBlockConstructor.h"
#include "ResourceManager.h"


std::shared_ptr<Block> ConcreteBlockConstructor::Construct()
{
	auto block = std::make_shared<Block>();
	block->SetTextureCoords(ResourceManager::GetWallCoords(Walls::Concrete));
	block->SetDepth(&Depth::Action);
	return block;
}
