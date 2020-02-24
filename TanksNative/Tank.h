#pragma once
#include <memory>

#include "GameObject.h"
#include "ITankController.h"
#include "TankType.h"
#include "TankLevel.h"
#include "Direction.h"
#include "Property.h"
#include "Bullet.h"


class Tank : public GameObject
{
	PROPERTY_CUSTOM_SET(TankLevel, Level, OnLevelChanged);
	PROPERTY_CUSTOM_SET(Direction, Direction, OnDirectionChanged);
	PROPERTY_GET(TankType, Type);
	std::shared_ptr<ITankController> controller;
	std::shared_ptr<Bullet> bullet;

	void OnLevelChanged(TankLevel level);
	void OnDirectionChanged(Direction direction);
	void XChanged(float newX);
	void YChanged(float newY);

public:
	Tank(std::shared_ptr<ITankController> controller, TankType type, TankLevel level);

	void Step(Direction direction);
	void Shot();

	virtual void Update(float elapsedTime) override;


};

