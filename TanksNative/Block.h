#pragma once

#include "ECS.h"
#include "Walls.h"
#include "Property.h"
#include "BoundsComponent.h"

struct Block : ECS::TComponent<Block> {
	Bounds* bounds;

	Walls Wall;

	virtual void Initialize(ECS::EntityID entityID) override;
	virtual void Render(ECS::EntityID entityID) override;
};