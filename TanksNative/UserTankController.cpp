#include "UserTankController.h"
#include "Tank.h"
#include "ResourceManager.h"
#include "Input.h"


void UserTankController::Update(Tank* const tank, float elapsedTime)
{
	if (Input::IskeyDown(L"W"))
	{
		tank->Step(Direction::Top);
	}
	else if (Input::IskeyDown(L"D"))
	{
		tank->Step(Direction::Right);
	}
	else if (Input::IskeyDown(L"S"))
	{
		tank->Step(Direction::Bottom);
	}
	else if (Input::IskeyDown(L"A"))
	{
		tank->Step(Direction::Left);
	}
	else if (Input::IskeyDown(L"J"))
	{
		tank->Shot();
	}
}

void UserTankController::GetTexture(Tank* const tank)
{
	tank->SetTextureCoords(ResourceManager::GetTankCoords(tank->GetType(), tank->GetDirection(), tank->GetLevel(), 0));
}
