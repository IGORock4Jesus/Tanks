#pragma once

#include <memory>
#include "Block.h"


__interface IBlockConstructor
{
	std::shared_ptr<Block> Construct();
};