#pragma once
#include "IBlockConstructor.h"


class IceBlockConstructor : public IBlockConstructor
{
	// ������������ ����� IBlockConstructor
	virtual std::shared_ptr<Block> Construct() override;
};

