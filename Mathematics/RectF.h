#pragma once

#include "MATHEMATICS_API.h"
#include "Vector2.h"

struct RectF {
	float x, y, width, height;
	inline float Left() { return x; }
	inline float Right() { return x + width; }
	inline float Top() { return y; }
	inline float Bottom() { return y + height; }
	inline void Offset(const Vector2& vec) {
		x += vec.x;
		y += vec.y;
	}
	inline Vector2 TopLeft() const { return { x, y }; }
	inline Vector2 TopRight() const { return { x + width, y }; }
	inline Vector2 BottomLeft() const { return { x, y + height }; }
	inline Vector2 BottomRight() const { return { x + width, y + height }; }
};