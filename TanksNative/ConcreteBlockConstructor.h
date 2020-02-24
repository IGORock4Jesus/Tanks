#pragma once
#include "IBlockConstructor.h"


class ConcreteBlockConstructor : public IBlockConstructor
{
	// Унаследовано через IBlockConstructor
	virtual std::shared_ptr<Block> Construct() override;
};

