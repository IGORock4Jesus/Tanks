#pragma once

#include "GameObject.h"
#include "Walls.h"
#include "Property.h"


class Block : public GameObject {
	PROPERTY_GET(Walls, Wall);

public:
	Block(Walls wall);
};