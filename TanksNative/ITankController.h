#pragma once

class Tank;

__interface ITankController
{
	void Update(Tank* const tank, float elapsedTime);
	void GetTexture(Tank* const tank);
};
