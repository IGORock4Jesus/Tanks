#include "WaterBlockConstructor.h"
#include "ResourceManager.h"


std::shared_ptr<Block> WaterBlockConstructor::Construct()
{
	auto block = std::make_shared<Block>();
	block->SetTextureCoords(ResourceManager::GetWallCoords(Walls::Water_1));
	block->SetDepth(&Depth::Ground);
	return block;
}
