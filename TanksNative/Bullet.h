#pragma once
#include "GameObject.h"
#include "Direction.h"
#include "BulletSpeed.h"


class Bullet : public GameObject
{
	PROPERTY(const BulletSpeed*, Speed);
	Direction direction;

public:
	Bullet(Direction direction);

	virtual void Update(float elapsedTime) override;
	virtual void OnCollisionDetected(std::shared_ptr<GameObject>& another) override;
};

