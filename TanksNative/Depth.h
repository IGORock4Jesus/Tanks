#pragma once

#include "Property.h"


class Depth {
	PROPERTY_GET(float, Value);

	Depth(float value) : _Value{ value } {}
public:

	static const Depth Ground;
	static const Depth Action;
	static const Depth Covers;
	static const Depth Bonuses;
};