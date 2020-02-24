#pragma once

class BulletSpeed {
	float value;
	BulletSpeed(float value)
		: value{ value } {}

public:
	static const BulletSpeed Normal;
	static const BulletSpeed Fast;

	float GetValue() const { return value; }
};