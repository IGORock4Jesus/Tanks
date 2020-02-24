#include "ForestBlockConstructor.h"
#include "ResourceManager.h"


std::shared_ptr<Block> ForestBlockConstructor::Construct()
{
	auto block = std::make_shared<Block>();
	block->SetTextureCoords(ResourceManager::GetWallCoords(Walls::Forest));
	block->SetDepth(&Depth::Covers);
	return block;
}
