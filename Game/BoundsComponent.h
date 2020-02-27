#pragma once

#include <Mathematics/RectF.h>
#include <ECS/Component.h>

struct BoundsComponent : ECS::TComponent<BoundsComponent>
{
	RectF rect;
};