#pragma once
#include "IBlockConstructor.h"


class VoidBlockConstructor : public IBlockConstructor
{
	// ������������ ����� IBlockConstructor
	virtual std::shared_ptr<Block> Construct() override;
};

