#pragma once

#include "MATHEMATICS_API.h"
#include "Vector2.h"

struct Vector3 {
	float x, y, z;
	Vector3(float x, float y, float z)
		: x{ x }, y{ y }, z{ z }{};
	Vector3()
		: Vector3{ 0.0f, 0.0f, 0.0f } {}
	Vector3(const Vector2& vec, float z)
		: Vector3{ vec.x, vec.y, z } {}
};
