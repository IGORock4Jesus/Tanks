#pragma once
#include "IBlockConstructor.h"


class ForestBlockConstructor : public IBlockConstructor
{
	// ������������ ����� IBlockConstructor
	virtual std::shared_ptr<Block> Construct() override;
};

