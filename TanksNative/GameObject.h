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

	GameObject();
	virtual void Render();
	virtual void Update(float elapsedTime);
};