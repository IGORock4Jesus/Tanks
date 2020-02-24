#pragma once

#include "Math.h"
#include "Depth.h"
#include "Property.h"
#include "Event.h"


class GameObject {
	PROPERTY(Vector2, Position);
	PROPERTY(Vector2, Size);
	PROPERTY(const Depth*, Depth);
	PROPERTY(RectF, TextureCoords);

public:
	Event<GameObject*> Destroyed;
	Event<GameObject*, std::shared_ptr<GameObject>&> CollisionDetected;

	GameObject();
	virtual void Render();
	virtual void Update(float elapsedTime);
	virtual void OnCollisionDetected(std::shared_ptr<GameObject>& another) {}

	void Destroy();
	void Collision(std::shared_ptr<GameObject>& another);
};