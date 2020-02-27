#pragma once

#include "MATHEMATICS_API.h"

struct Vector2 {
	float x, y;
	Vector2 operator + (const Vector2& another) {
		return { x + another.x, y + another.y };
	}
	Vector2 operator - (const Vector2& another) {
		return { x - another.x,y - another.y };
	}
	Vector2 operator * (float scale) {
		return { x * scale, y * scale };
	}
	void operator += (const Vector2& another) {
		x += another.x;
		y += another.y;
	}
};
