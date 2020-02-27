#pragma once

#include "Math.h"
#include "ECS.h"
#include "Property.h"


struct Bounds : ECS::TComponent<Bounds> {
	RectF rect;
};

