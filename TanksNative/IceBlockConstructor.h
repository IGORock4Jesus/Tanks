#pragma once
#include "IBlockConstructor.h"


class IceBlockConstructor : public IBlockConstructor
{
	// Унаследовано через IBlockConstructor
	virtual std::shared_ptr<Block> Construct() override;
};

