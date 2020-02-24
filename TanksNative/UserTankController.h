#pragma once

#include "ITankController.h"


class UserTankController : public ITankController
{
public:
	// ������������ ����� ITankController
	virtual void Update(Tank* const tank, float elapsedTime) override;
	virtual void GetTexture(Tank* const tank) override;
};

