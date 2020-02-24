#pragma once

#include "IBlockConstructor.h"


class BrickBlockConstructor : public IBlockConstructor
{
	// Унаследовано через IBlockConstructor
	virtual std::shared_ptr<Block> Construct() override;
};

