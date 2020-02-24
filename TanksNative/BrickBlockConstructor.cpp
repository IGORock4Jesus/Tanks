#include "BrickBlockConstructor.h"
#include "ResourceManager.h"


std::shared_ptr<Block> BrickBlockConstructor::Construct()
{
	auto block = std::make_shared<Block>();
	block->SetTextureCoords(ResourceManager::GetWallCoords(Walls::Brick_Whole));
	block->SetDepth(&Depth::Action);
	return block;
}
