#include "IceBlockConstructor.h"
#include "ResourceManager.h"	


std::shared_ptr<Block> IceBlockConstructor::Construct()
{
	auto block = std::make_shared<Block>();
	block->SetTextureCoords(ResourceManager::GetWallCoords(Walls::Ice));
	block->SetDepth(&Depth::Ground);
	return block;
}
