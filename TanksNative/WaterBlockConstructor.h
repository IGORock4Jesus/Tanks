#pragma once
#include "IBlockConstructor.h"


class WaterBlockConstructor : public IBlockConstructor
{
	// ������������ ����� IBlockConstructor
	virtual std::shared_ptr<Block> Construct() override;
};

