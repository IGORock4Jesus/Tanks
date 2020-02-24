#pragma once

#include <d3dx9.h>

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

struct Vector3 {
	float x, y, z;
	Vector3(float x, float y, float z)
		: x{ x }, y{ y }, z{ z }{};
	Vector3()
		: Vector3{ 0.0f, 0.0f, 0.0f } {}
	Vector3(const Vector2& vec, float z)
		: Vector3{ vec.x, vec.y, z }{}

	operator D3DXVECTOR3() {
		return { x, y, z };
	}
};

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