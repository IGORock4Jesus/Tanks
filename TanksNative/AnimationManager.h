#pragma once

#include <map>
#include <memory>
#include "Event.h"

namespace AnimationManager
{
struct Animation
{
	float length{ 0.0f };
	Event<float> callback;
	float cursor{ 0.0f };
	bool looped{ false };
	std::map<float, float> frames;
};


void Update(float elapsedTime);

void Add(std::shared_ptr<Animation> animation);

};

