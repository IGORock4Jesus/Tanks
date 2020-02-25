#pragma once
#include "GameObject.h"
#include "Direction.h"
#include "BulletSpeed.h"


class Bullet : public GameObject
{
	PROPERTY(const BulletSpeed*, Speed);
	Direction direction;

	void OnCollisionDetected(std::shared_ptr<GameObject>& a, std::shared_ptr<GameObject>& b);
public:
	Bullet(Direction direction);
	~Bullet();

	virtual void Update(float elapsedTime) override;
};

