#pragma once
#include "IBlockConstructor.h"


class ConcreteBlockConstructor : public IBlockConstructor
{
	// ������������ ����� IBlockConstructor
	virtual std::shared_ptr<Block> Construct() override;
};

